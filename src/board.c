#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "board.h"

static void print_box(int box) {
  if (box == EMPTY)
    printf(".");
  else if (box == WHITE)
    printf("O");
  else if (box == BLACK)
    printf("X");
  else if (box == WALL)
    printf("#");
}

void Board_print(const Board *self) {
  printf("\033[H\033[2J");
  printf("==== AI-reversi ====\n");
  printf("   A B C D E F G H\n");
  for (int i = BOARD_SIZE; i <= (BOARD_SIZE + 2) * BOARD_SIZE; i++) {
    if (i % (BOARD_SIZE + 1) == 0)
      printf(" %d ", i / (BOARD_SIZE + 1));
    if (self->box[i] == WALL)
      continue;
    print_box(self->box[i]);
    printf(" ");
    if (i % 9 == 8)
      printf("\n");
  }
  printf("\n O: %d, X: %d, .: %d\n", self->white, self->black, self->empty);
}

void Board_make_box(Board *self, const char str[]) {
  if (str == NULL || strlen(str) < BOARD_SIZE * BOARD_SIZE)
    exit(EXIT_FAILURE);

  self->empty = 0;
  self->white = 0;
  self->black = 0;

  for (int i = 0; i < BOX_SIZE; i++) {
    if (i < 9 || i % 9 == 0 || i > 80) {
      self->box[i] = WALL;
      continue;
    }

    while (*str == ' ')
      str++;
    if (*str == '.') {
      self->box[i] = EMPTY;
      self->empty++;
      str++;
    } else if (*str == 'O') {
      self->box[i] = WHITE;
      self->white++;
      str++;
    } else if (*str == 'X') {
      self->box[i] = BLACK;
      self->black++;
      str++;
    } else
      exit(EXIT_FAILURE);
  }
}

void Board_init(Board *board) {
  Board_make_box(board, ""
      "........"
      "........"
      "........"
      "...OX..."
      "...XO..."
      "........"
      "........"
      "........");
}

void Board_rewrite(Board *dest, const Board *src) {
  dest->white = src->white;
  dest->black = src->black;
  dest->empty = src->empty;
  for (int i = 0; i < BOX_SIZE; i++)
    dest->box[i] = src->box[i];
}
