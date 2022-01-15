#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ai-reversi.h"
#include "board.h"
#include "rule.h"

int Rule_other_color(int color) {
  if (color == WHITE)
    return BLACK;
  if (color == BLACK)
    return WHITE;
  exit(EXIT_FAILURE);
}

static int reverse_line(int box[], int color, int init_pos, int dir) {
  int other = Rule_other_color(color);
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

/*
 * 1 <= x <= 8
 * 1 <= y <= 8
 */
int Rule_set(Board *board, int x, int y, int color) {
  int p = POS(x, y);
  if (board->box[p] != EMPTY)
    return 0;

  int count = 0;
  count += reverse_line(board->box, color, p, DIR_UP_LEFT);
  count += reverse_line(board->box, color, p, DIR_UP);
  count += reverse_line(board->box, color, p, DIR_UP_RIGHT);
  count += reverse_line(board->box, color, p, DIR_LEFT);
  count += reverse_line(board->box, color, p, DIR_RIGHT);
  count += reverse_line(board->box, color, p, DIR_DOWN_LEFT);
  count += reverse_line(board->box, color, p, DIR_DOWN);
  count += reverse_line(board->box, color, p, DIR_DOWN_RIGHT);
  if (count == 0)
    return 0;

  board->box[p] = color;
  count++;
  if (color == WHITE) {
    board->white += count;
    board->black -= count - 1;
  } else {
    board->white -= count - 1;
    board->black += count;
  }
  board->empty--;

  return count;
}

int Rule_set_by_str(Board *board, const char str[], int color) {
  if (strlen(str) != 2)
    return 0;
  int first_char = toupper(str[0]);
  if (first_char < 'A' || 'H' < first_char)
    return 0;
  if (str[1] < '1' || '8' < str[1])
    return 0;
  int x = first_char - 'A' + 1;
  int y = str[1] - '1' + 1;

  return Rule_set(board, x, y, color);
}

static int can_set_line(const int box[], int color, int init_pos, int dir) {
  int other = Rule_other_color(color);
  int pos;

  for (pos = init_pos + dir; box[pos] == other; pos += dir);
  if (pos == init_pos + dir)
    return NG;
  if (box[pos] != color)
    return NG;
  return OK;
}

int Rule_can_set(const Board *board, int x, int y, int color) {
  int p = POS(x, y);
  if (board->box[p] != EMPTY)
    return NG;

  if (can_set_line(board->box, color, p, DIR_UP_LEFT) == OK)
    return OK;
  if (can_set_line(board->box, color, p, DIR_UP) == OK)
    return OK;
  if (can_set_line(board->box, color, p, DIR_UP_RIGHT) == OK)
    return OK;
  if (can_set_line(board->box, color, p, DIR_LEFT) == OK)
    return OK;
  if (can_set_line(board->box, color, p, DIR_RIGHT) == OK)
    return OK;
  if (can_set_line(board->box, color, p, DIR_DOWN_LEFT) == OK)
    return OK;
  if (can_set_line(board->box, color, p, DIR_DOWN) == OK)
    return OK;
  if (can_set_line(board->box, color, p, DIR_DOWN_RIGHT) == OK)
    return OK;
  return NG;
}

int Rule_can_pass(const Board *board, int color) {
  for (int y = 1; y <= BOARD_SIZE; y++)
    for (int x = 1; x <= BOARD_SIZE; x++)
      if (Rule_can_set(board, x, y, color) == OK)
        return NG;
  return OK;
}
