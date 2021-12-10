#include <stdio.h>
#include <stdlib.h>
#include "ai-reversi.h"
#include "board.h"

void  print_box(int box) {
  if (box == EMPTY)
    printf(".");
  else if (box == WHITE)
    printf("O");
  else if (box == BLACK)
    printf("X");
  else if (box == WALL)
    printf("#");
}

void  print(Board *this) {
  printf("   A B C D E F G H\n");
  for (int i = BOARD_SIZE; i <= (BOARD_SIZE + 2) * BOARD_SIZE; i++) {
    if (i % (BOARD_SIZE + 1) == 0)
      printf(" %d ", i / (BOARD_SIZE + 1));
    if (this->box[i] == WALL)
      continue;
    print_box(this->box[i]);
    printf(" ");
    if (i % 9 == 8)
      printf("\n");
  }
}

void  Board_init(Board *board) {
  // init box
  for (int i = 0; i < BOX_SIZE; i++) {
    if (i <= BOARD_SIZE || i > (BOARD_SIZE + 2) * BOARD_SIZE || i % (BOARD_SIZE + 1) == 0)
      board->box[i] = WALL;
    else
      board->box[i] = EMPTY;
  }
  board->box[40] = WHITE;
  board->box[50] = WHITE;
  board->box[41] = BLACK;
  board->box[49] = BLACK;

  // set method
  board->print = print;
}

Board *Board_new(void) {
  Board *board = malloc(sizeof(Board));
  if (board == NULL) {
    puts("ERROR: failure malloc() Board");
    exit(EXIT_ERR);
  }

  Board_init(board);

  return board;
}

void Board_delete(Board *board) {
  free(board);
}
