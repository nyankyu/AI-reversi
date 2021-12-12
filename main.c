#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai-reversi.h"
#include "board.h"

#define BUFF_SIZE 256

void get_input(char buff[]) {
  if (fgets(buff, BUFF_SIZE, stdin) == NULL) {
    exit(EXIT_ERR);
  }
  *strchr(buff, '\n') = '\0';
}

int main(void) {
  Board *board = Board_new();

  char buff[BUFF_SIZE];
  while (1) {
    board->print(board);

    get_input(buff);
    if (strcmp(buff, "q") == 0)
      exit(EXIT_OK);
    board->set_by_str(board, buff);
  }

  Board_delete(board);

  return EXIT_OK;
}


