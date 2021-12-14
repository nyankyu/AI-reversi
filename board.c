#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "ai-reversi.h"
#include "board.h"

static void  print_box(int box) {
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
  printf("\033[H\033[2J");
  printf("===== AI-reversi =====\n");
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
  printf("\n O: %d, X: %d, .: %d\n", this->white, this->black, this->empty);
}

void  Board_init(Board *board) {
  // set method
  board->print = print;

  board->empty = BOARD_SIZE * BOARD_SIZE - 4;
  board->white = 2;
  board->black = 2;

  // init box
  for (int i = 0; i < BOX_SIZE; i++) {
    if (i <= BOARD_SIZE || i > (BOARD_SIZE + 2) * BOARD_SIZE || i % (BOARD_SIZE + 1) == 0)
      board->box[i] = WALL;
    else
      board->box[i] = EMPTY;
  }
  board->box[POS(4, 4)] = WHITE;
  board->box[POS(5, 5)] = WHITE;
  board->box[POS(4, 5)] = BLACK;
  board->box[POS(5, 4)] = BLACK;
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
