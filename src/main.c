#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai-reversi.h"
#include "board.h"
#include "com.h"
#include "history.h"
#include "player.h"
#include "human.h"

static void print_prompt(int next_color) {
  printf("\n %c > ", next_color == WHITE ? 'O' : 'X');
}


int main(int argc, char **argv) {
  int ai_vs_ai = FALSE;
  if (argc == 2 && strcmp("auto", argv[1]) == 0) {
    ai_vs_ai = TRUE;
  }

  Player *black;
  Player *white;
  Player *player;
  Board *board = Board_new();
  History *history = History_new();
  int next_color = BLACK;
  int pass = 0;

  if (ai_vs_ai == TRUE)
    black = Com_make_player(BLACK);
  else
    black = Human_make_player(BLACK);
  white = Com_make_player(WHITE);
  player = black;
  Board_init(board);
  History_add(history, board, BLACK);

  while (1) {
    Board_print(board);
    print_prompt(next_color);

    int result = player->next(player, board);
    if (result == PLAYER_PUT) {
      pass = 0;
    } else if (result == PLAYER_PASS) {
      if (pass == 1)
        break;
      pass++;
    } else if (result == PLAYER_QUIT) {
      break;
    } else if (result == PLAYER_UNDO) {
      History_undo(history);
      Board_rewrite(board, history->board_array[history->current]);
    } else if (result == PLAYER_ERR){
      exit(EXIT_ERR);
    } else if (result == PLAYER_NG) {
      continue;
    }
    History_add(history, board, next_color);
    player = (player == white) ? black : white;
    next_color = Rule_other_color(next_color);
  }

  History_delete(history);
  Board_delete(board);
  black->Player_delete(black);
  white->Player_delete(white);

  //system("leaks ai-reversi");
  return EXIT_OK;
}


