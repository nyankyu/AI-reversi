#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

int pos(int x, int y) {
  return (BOARD_SIZE + 1) * y + x;
}

/*
 * 1 <= x <= 8
 * 1 <= y <= 8
 * v: EMPTY, WHITE, BLACK
 */
void set_box(Board *this, int x, int y, int v) {
  assert(1 <= x);
  assert(x <= 8);
  assert(1 <= y);
  assert(y <= 8);
  this->box[pos(x, y)] = v;
}

void reverse(Board *this, int x, int y) {
  int color = this->box[pos(x, y)];
  if (color == WHITE)
    this->box[pos(x, y)] = BLACK;
  if (color == BLACK)
    this->box[pos(x, y)] = WHITE;
}

void  Board_init(Board *board) {
  // set method
  board->print = print;
  board->set_box = set_box;
  board->reverse = reverse;

  // init box
  for (int i = 0; i < BOX_SIZE; i++) {
    if (i <= BOARD_SIZE || i > (BOARD_SIZE + 2) * BOARD_SIZE || i % (BOARD_SIZE + 1) == 0)
      board->box[i] = WALL;
    else
      board->box[i] = EMPTY;
  }
  board->set_box(board, 4, 4, WHITE);
  board->set_box(board, 5, 5, WHITE);
  board->set_box(board, 4, 5, BLACK);
  board->set_box(board, 5, 4, BLACK);
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
