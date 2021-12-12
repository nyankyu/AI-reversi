#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai-reversi.h"
#include "board.h"
#include "com.h"

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
  Board *board = Board_new();
  Com *com = Com_new(BLACK);
  int eval_val;

  char buff[BUFF_SIZE];
  while (1) {
    board->print(board);

    get_input(buff);
    if (strcmp(buff, "q") == 0)
      exit(EXIT_OK);
    if (board->set_by_str(board, buff) == 0)
      continue;

    int next = com->next(com, board, &eval_val);
    board->set_by_index(board, next);
  }

  Board_delete(board);

  return EXIT_OK;
}


