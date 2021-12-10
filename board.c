#include <stdio.h>
#include "board.h"

void  print_box(int box) {
  if (box == EMPTY)
    printf(".");
  else if (box == WHITE)
    printf("O");
  else if (box == BRACK)
    printf("X");
  else if (box == WALL)
    printf("#");
}

void  print(Board *this) {
  printf("   A B C D E F G H");
  for (int i = BOARD_SIZE; i <= (BOARD_SIZE + 2) * BOARD_SIZE; i++) {
    if (i % (BOARD_SIZE + 1) == 0)
      printf("\n %d ", i / (BOARD_SIZE + 1));
    if (this->box[i] == WALL)
      continue;
    print_box(this->box[i]);
    printf(" ");
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

  // set method
  board->print = print;
}
