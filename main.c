#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ai-reversi.h"
#include "board.h"

#define BUFF_SIZE 256

void get_input(char buff[]) {
  if (fgets(buff, BUFF_SIZE, stdin) == NULL) {
    exit(EXIT_ERR);
  }
  for (; *buff != '\n'; buff++);
  *buff = '\0';
}

void get_pos(char buff[], int *x, int *y) {
  buff[0] = toupper(buff[0]);
  if (buff[0] < 'A' || 'H' < buff[0])
    continue;
  if (buff[1] < '1' || '8' < buff[1])
    continue;
  *x = buff[0] - 'A' + 1;
  *y = buff[1] - '1' + 1;
}

int main(void) {
  Board *board = Board_new();

  char buff[BUFF_SIZE];
  int x, y;

  while (1) {
    board->print(board);

    get_input(buff);
    if (strcmp(buff, "q") == 0)
      exit(EXIT_OK);
    if (strlen(buff) != 2)
      continue;
    get_pos(buff, &x, &y);
    board->set(board, x, y);
  }

  Board_delete(board);

  return EXIT_OK;
}


