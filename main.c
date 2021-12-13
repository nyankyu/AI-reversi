#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai-reversi.h"
#include "board.h"
#include "com.h"
#include "game.h"

#define BUFF_SIZE 256

void get_input(char buff[]) {
  if (fgets(buff, BUFF_SIZE, stdin) == NULL) {
    exit(EXIT_ERR);
  }
  char *p = strchr(buff, '\n');
  if (p != NULL)
    *p = '\0';
}

int main(void) {
  Game *game = Game_new();
  Board *board = Board_new();
  Com *com = Com_new(BLACK);
  int eval_val;
  int pass_other = 0;

  char buff[BUFF_SIZE];
  while (1) {
    board->print(board);

    if (game->can_pass(game, board) == NG) {
      get_input(buff);
      if (strcmp(buff, "q") == 0)
        exit(EXIT_OK);
      if (game->set_by_str(game, board, buff) == 0)
        continue;
      pass_other = 0;
    } else {
      pass_other = 1;
    }

    int next = com->next(com, game, board, &eval_val);
    if (next == 0) {
      if (pass_other == 1)
        exit(EXIT_OK);
      pass_other = 1;
      continue;
    }
    game->set_by_index(game, board, next);
    pass_other = 0;
  }

  Board_delete(board);

  return EXIT_OK;
}


