#include "evaluator.h"
#include "rule.h"
#include "ai-reversi.h"

static inline int available_point(const Board *board, int next_color) {
  int count = 0;

  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (Rule_can_set(board, x, y, next_color) == OK) {
        count++;
      }
    }
  }
  return count;
}

static inline int important_point(const Board *board, int next_color) {
  int point = 0;
  int other_color = Rule_other_color(next_color);

  if (board->box[A1] == next_color)
    point += CORNER_POINT;
  else if (board->box[A1] == other_color)
    point -= CORNER_POINT;
  else {
    if (board->box[B1] == next_color)
      point -= C_POINT;
    if (board->box[A2] == next_color)
      point -= C_POINT;
    if (board->box[B2] == next_color)
      point -= X_POINT;
    if (board->box[B1] == other_color)
      point += C_POINT;
    if (board->box[A2] == other_color)
      point += C_POINT;
    if (board->box[B2] == other_color)
      point += X_POINT;
  }

  if (board->box[H1] == next_color)
    point += CORNER_POINT;
  else if (board->box[H1] == other_color)
    point -= CORNER_POINT;
  else {
    if (board->box[G1] == next_color)
      point -= C_POINT;
    if (board->box[H2] == next_color)
      point -= C_POINT;
    if (board->box[G2] == next_color)
      point -= X_POINT;
    if (board->box[G1] == other_color)
      point += C_POINT;
    if (board->box[H2] == other_color)
      point += C_POINT;
    if (board->box[G2] == other_color)
      point += X_POINT;
  }

  if (board->box[A8] == next_color)
    point += CORNER_POINT;
  else if (board->box[A8] == other_color)
    point -= CORNER_POINT;
  else {
    if (board->box[B8] == next_color)
      point -= C_POINT;
    if (board->box[A7] == next_color)
      point -= C_POINT;
    if (board->box[B7] == next_color)
      point -= X_POINT;
    if (board->box[B8] == other_color)
      point += C_POINT;
    if (board->box[A7] == other_color)
      point += C_POINT;
    if (board->box[B7] == other_color)
      point += X_POINT;
  }

  if (board->box[H8] == next_color)
    point += CORNER_POINT;
  else if (board->box[H8] == other_color)
    point -= CORNER_POINT;
  else {
    if (board->box[G8] == next_color)
      point -= C_POINT;
    if (board->box[H7] == next_color)
      point -= C_POINT;
    if (board->box[G7] == next_color)
      point -= X_POINT;
    if (board->box[G8] == other_color)
      point += C_POINT;
    if (board->box[H7] == other_color)
      point += C_POINT;
    if (board->box[G7] == other_color)
      point += X_POINT;
  }

  return point;
}

void Evaluator_evaluate(const Board *board, int next_color, int *eval_point) {
  int available = available_point(board, next_color);
  int important = important_point(board, next_color);
  *eval_point = available + important;
}

