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

static void usage(void) {
  printf("usage: ai-reversi [option]\n");
  printf("option\n");
  printf("\t(none)      The same as \"black\"\n");
  printf("\tauto        AI vs AI\n");
  printf("\twhite       Human vs AI. Human is White. AI is Black.\n");
  printf("\tblack       Human vs AI. Human is Black. AI is White.\n");
  printf("\tvs_human    Human vs Human\n");
}

static void judge(Board *board) {
  printf("\n\n");
  if (board->white > board->black)
    printf("\tO WIN\n");
  else if (board->white < board->black)
    printf("\tX WIN\n");
  else
    printf("\tDRAW\n");
}

int main(int argc, char **argv) {
  Player *black;
  Player *white;
  Player *player;
  Board *board = Board_new();
  History *history = History_new();
  int pass = 0;

  if (argc == 1) {
    white = Com_make_player(WHITE);
    black = Human_make_player(BLACK);
  } else if (argc != 2) {
    usage();
    exit(EXIT_ERR);
  } else if (strcmp("auto", argv[1]) == 0) {
    white = Com_make_player(WHITE);
    black = Com_make_player(BLACK);
  } else if (strcmp("white", argv[1]) == 0) {
    white = Human_make_player(WHITE);
    black = Com_make_player(BLACK);
  } else if (strcmp("black", argv[1]) == 0) {
    white = Com_make_player(WHITE);
    black = Human_make_player(BLACK);
  } else if (strcmp("vs_human", argv[1]) == 0) {
    white = Human_make_player(WHITE);
    black = Human_make_player(BLACK);
  } else {
    usage();
    exit(EXIT_ERR);
  }

  player = black;
  Board_init(board);
  History_add(history, board, BLACK);

  while (1) {
    Board_print(board);
    print_prompt(player->color);

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
      History_undo(history);
      Board_rewrite(board, history->board_array[history->current]);
      if (history->current == 0)
        player = black;
      continue;
    } else if (result == PLAYER_ERR){
      exit(EXIT_ERR);
    } else if (result == PLAYER_NG) {
      continue;
    }
    History_add(history, board, player->color);
    player = (player == white) ? black : white;
  }

  judge(board);

  History_delete(history);
  Board_delete(board);
  black->Player_delete(black);
  white->Player_delete(white);

  //system("leaks ai-reversi");
  return EXIT_OK;
}


