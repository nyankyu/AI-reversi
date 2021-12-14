#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
int set(Board *board, int x, int y) {
  int p = POS(x, y);
  if (board->box[p] != EMPTY)
    return 0;

  int count = 0;
  count += reverse_line(board->box, board->next_color, p, DIR_UP_LEFT);
  count += reverse_line(board->box, board->next_color, p, DIR_UP);
  count += reverse_line(board->box, board->next_color, p, DIR_UP_RIGHT);
  count += reverse_line(board->box, board->next_color, p, DIR_LEFT);
  count += reverse_line(board->box, board->next_color, p, DIR_RIGHT);
  count += reverse_line(board->box, board->next_color, p, DIR_DOWN_LEFT);
  count += reverse_line(board->box, board->next_color, p, DIR_DOWN);
  count += reverse_line(board->box, board->next_color, p, DIR_DOWN_RIGHT);
  if (count == 0)
    return 0;

  board->box[p] = board->next_color;
  count++;
  if (board->next_color == WHITE) {
    board->white += count;
    board->black -= count - 1;
  } else {
    board->white -= count - 1;
    board->black += count;
  }
  board->empty--;

  board->next_color = other_color(board->next_color);
  return count;
}

int set_by_str(Board *board, char str[]) {
  if (strlen(str) != 2)
    return 0;
  str[0] = toupper(str[0]);
  if (str[0] < 'A' || 'H' < str[0])
    return 0;
  if (str[1] < '1' || '8' < str[1])
    return 0;
  int x = str[0] - 'A' + 1;
  int y = str[1] - '1' + 1;

  return set(board, x, y);
}

int set_by_index(Board *board, int index) {
  int x = index % 9;
  int y = index / 9;
  return set(board, x, y);
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

int can_set(Board *board, int x, int y) {
  int p = POS(x, y);
  if (board->box[p] != EMPTY)
    return NG;

  if (can_set_line(board->box, board->next_color, p, DIR_UP_LEFT) == OK)
    return OK;
  if (can_set_line(board->box, board->next_color, p, DIR_UP) == OK)
    return OK;
  if (can_set_line(board->box, board->next_color, p, DIR_UP_RIGHT) == OK)
    return OK;
  if (can_set_line(board->box, board->next_color, p, DIR_LEFT) == OK)
    return OK;
  if (can_set_line(board->box, board->next_color, p, DIR_RIGHT) == OK)
    return OK;
  if (can_set_line(board->box, board->next_color, p, DIR_DOWN_LEFT) == OK)
    return OK;
  if (can_set_line(board->box, board->next_color, p, DIR_DOWN) == OK)
    return OK;
  if (can_set_line(board->box, board->next_color, p, DIR_DOWN_RIGHT) == OK)
    return OK;
  return NG;
}

int can_pass(Board *board) {
  for (int y = 1; y <= BOARD_SIZE; y++)
    for (int x = 1; x <= BOARD_SIZE; x++)
      if (can_set(board, x, y) == OK)
        return NG;
  return OK;
}


void Rule_init(Rule *rule) {
  rule->history = 0;
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

  Rule_init(rule);
  return rule;
}

void Rule_delete(Rule *rule) {
  free(rule);
}
