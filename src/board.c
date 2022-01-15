#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ai-reversi.h"
#include "board.h"

Board g_boardPool[BOARD_POOL_SIZE];
int g_boardPoolIndex = 0;

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
    exit(EXIT_ERR);

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
      exit(EXIT_ERR);
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

Board *Board_new(void) {
  if (g_boardPoolIndex == BOARD_POOL_SIZE)
    exit(EXIT_ERR);
  return &g_boardPool[g_boardPoolIndex++];
}

/**
 * Release board. Do note perform free().
 * We only consider the number of new and delete operations,
 * but this implementation is fine because Board_delete() is
 * called at the same time when the program finishes using
 * all the boards.
 * @param board
 */
void Board_delete(Board *board) {
  if (board == NULL)
    return;
  if (g_boardPoolIndex == 0)
    exit(EXIT_ERR);
  g_boardPoolIndex--;
}

Board *Board_copy(const Board *source) {
  Board *copy = Board_new();
  copy->empty = source->empty;
  copy->white = source->white;
  copy->black = source->black;
  for (int i = 0; i < BOX_SIZE; i++)
    copy->box[i] = source->box[i];
  return copy;
}

void Board_rewrite(Board *dest, const Board *src) {
  dest->white = src->white;
  dest->black = src->black;
  dest->empty = src->empty;
  for (int i = 0; i < BOX_SIZE; i++)
    dest->box[i] = src->box[i];
}
