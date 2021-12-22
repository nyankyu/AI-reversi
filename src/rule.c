#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ai-reversi.h"
#include "board.h"
#include "rule.h"

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

/*
 * 1 <= x <= 8
 * 1 <= y <= 8
 */
static int set(Board *board, int x, int y, int color) {
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

static int set_by_str(Board *board, const char str[], int color) {
  if (strlen(str) != 2)
    return 0;
  int first_char = toupper(str[0]);
  if (first_char < 'A' || 'H' < first_char)
    return 0;
  if (str[1] < '1' || '8' < str[1])
    return 0;
  int x = first_char - 'A' + 1;
  int y = str[1] - '1' + 1;

  return set(board, x, y, color);
}

static int set_by_index(Board *board, int index, int color) {
  int x = index % 9;
  int y = index / 9;
  return set(board, x, y, color);
}

static int can_set_line(const int box[], int color, int init_pos, int dir) {
  int other = other_color(color);
  int pos;

  for (pos = init_pos + dir; box[pos] == other; pos += dir);
  if (pos == init_pos + dir)
    return NG;
  if (box[pos] != color)
    return NG;
  return OK;
}

static int can_set(const Board *board, int x, int y, int color) {
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

static int can_pass(const Board *board, int color) {
  for (int y = 1; y <= BOARD_SIZE; y++)
    for (int x = 1; x <= BOARD_SIZE; x++)
      if (can_set(board, x, y, color) == OK)
        return NG;
  return OK;
}


void Rule_init(Rule *rule) {
  // dummy use rule
  if (rule == NULL)
    exit(EXIT_ERR);
}

Rule *Rule_new(void) {
  Rule *rule = malloc(sizeof(Rule));
  if (rule == NULL) {
    printf("ERROR: malloc() Rule-class\n");
    exit(EXIT_ERR);
  }

  rule->set = set;
  rule->set_by_str = set_by_str;
  rule->set_by_index = set_by_index;
  rule->can_set = can_set;
  rule->can_pass = can_pass;
  rule->other_color = other_color;

  Rule_init(rule);
  return rule;
}

void Rule_delete(Rule *rule) {
  free(rule);
}
