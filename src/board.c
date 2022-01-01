#include <stdio.h>
#include <stdlib.h>
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

static void  print(const Board *self) {
  printf("\033[H\033[2J");
  printf("===== AI-reversi =====\n");
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

static void make_box(Board *self, const char str[]) {
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

void  Board_init(Board *board) {
  board->empty = BOARD_SIZE * BOARD_SIZE - 4;
  board->white = 2;
  board->black = 2;

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

  board->print = print;
  board->make_box = make_box;

  return board;
}

void Board_delete(Board *board) {
  free(board);
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
