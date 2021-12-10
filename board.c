#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ai-reversi.h"
#include "board.h"

static int other_color(int color) {
  if (color == WHITE)
    return BLACK;
  if (color == BLACK)
    return WHITE;
  exit(EXIT_ERR);
}

static int reverse_line(int box[], int color, int init_pos, int dir) {
  int other = other_color(color);
  int pos;
  int count = 0;

  for (pos = init_pos + dir; box[pos] == other; pos += dir);
  if (box[pos] != color)
    return 0;
  for (pos -= dir; pos != init_pos; pos -= dir) {
    box[pos] = color;
    count++;
  }
  return count;
}

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

static int pos(int x, int y) {
  return (BOARD_SIZE + 1) * y + x;
}

/*
 * 1 <= x <= 8
 * 1 <= y <= 8
 * v: EMPTY, WHITE, BLACK
 */
int set(Board *this, int x, int y, int color) {
  int p = pos(x, y);
  if (this->box[p] != EMPTY)
    return 0;

  int count = 0;
  count += reverse_line(this->box, color, p, DIR_UP_LEFT);
  count += reverse_line(this->box, color, p, DIR_UP);
  count += reverse_line(this->box, color, p, DIR_UP_RIGHT);
  count += reverse_line(this->box, color, p, DIR_LEFT);
  count += reverse_line(this->box, color, p, DIR_RIGHT);
  count += reverse_line(this->box, color, p, DIR_DOWN_LEFT);
  count += reverse_line(this->box, color, p, DIR_DOWN);
  count += reverse_line(this->box, color, p, DIR_DOWN_RIGHT);
  if (count == 0)
    return 0;
  this->box[p] = color;
  return count;
}

static int can_set_line(int box[], int color, int init_pos, int dir) {
  int other = other_color(color);
  int pos;

  for (pos = init_pos + dir; box[pos] == other; pos += dir);
  if (pos == init_pos + dir)
    return NG;
  if (box[pos] != color)
    return NG;
  return OK;
}

int can_set(Board *this, int x, int y, int color) {
  int p = pos(x, y);
  if (this->box[p] != EMPTY)
    return NG;

  if (can_set_line(this->box, color, p, DIR_UP_LEFT) == OK)
    return OK;
  if (can_set_line(this->box, color, p, DIR_UP) == OK)
    return OK;
  if (can_set_line(this->box, color, p, DIR_UP_RIGHT) == OK)
    return OK;
  if (can_set_line(this->box, color, p, DIR_LEFT) == OK)
    return OK;
  if (can_set_line(this->box, color, p, DIR_RIGHT) == OK)
    return OK;
  if (can_set_line(this->box, color, p, DIR_DOWN_LEFT) == OK)
    return OK;
  if (can_set_line(this->box, color, p, DIR_DOWN) == OK)
    return OK;
  if (can_set_line(this->box, color, p, DIR_DOWN_RIGHT) == OK)
    return OK;
  return NG;
}

void  Board_init(Board *board) {
  // set method
  board->print = print;
  board->set = set;
  board->can_set = can_set;

  // init box
  for (int i = 0; i < BOX_SIZE; i++) {
    if (i <= BOARD_SIZE || i > (BOARD_SIZE + 2) * BOARD_SIZE || i % (BOARD_SIZE + 1) == 0)
      board->box[i] = WALL;
    else
      board->box[i] = EMPTY;
  }
  board->box[pos(4, 4)] = WHITE;
  board->box[pos(5, 5)] = WHITE;
  board->box[pos(4, 5)] = BLACK;
  board->box[pos(5, 4)] = BLACK;
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
