#include <limits.h>
#include "evaluator.h"
#include "rule.h"
#include "ai-reversi.h"

#define CORNER_POINT  80
#define X_POINT       50
#define C_POINT       30

static inline int available_point(Node *node) {
  int count_white = 0;
  int count_black = 0;

  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (Rule_can_set(&node->board, x, y, WHITE) == OK) {
        if (node->next_color == WHITE)
          count_white++;
        else
          count_black++;
      }
    }
  }
  if (count_white + count_black == 0)
    return INT_MAX;
  return count_white - count_black;
}

static inline int important_point(Node *node) {
  int point = 0;

  if (node->board.box[A1] == WHITE)
    point += CORNER_POINT;
  else if (node->board.box[A1] == EMPTY) {
    if (node->board.box[B1] == WHITE)
      point -= C_POINT;
    if (node->board.box[A2] == WHITE)
      point -= C_POINT;
    if (node->board.box[B2] == WHITE)
      point -= X_POINT;
  }

  if (node->board.box[H1] == WHITE)
    point += CORNER_POINT;
  else if (node->board.box[H1] == EMPTY) {
    if (node->board.box[G1] == WHITE)
      point -= C_POINT;
    if (node->board.box[H2] == WHITE)
      point -= C_POINT;
    if (node->board.box[G2] == WHITE)
      point -= X_POINT;
  }

  if (node->board.box[A8] == WHITE)
    point += CORNER_POINT;
  else if (node->board.box[A8] == EMPTY) {
    if (node->board.box[B8] == WHITE)
      point -= C_POINT;
    if (node->board.box[A7] == WHITE)
      point -= C_POINT;
    if (node->board.box[B7] == WHITE)
      point -= X_POINT;
  }

  if (node->board.box[H8] == WHITE)
    point += CORNER_POINT;
  else if (node->board.box[H8] == EMPTY) {
    if (node->board.box[G8] == WHITE)
      point -= C_POINT;
    if (node->board.box[H7] == WHITE)
      point -= C_POINT;
    if (node->board.box[G7] == WHITE)
      point -= X_POINT;
  }

  if (node->board.box[A1] == BLACK)
    point -= CORNER_POINT;
  else if (node->board.box[A1] == EMPTY) {
    if (node->board.box[B1] == BLACK)
      point += C_POINT;
    if (node->board.box[A2] == BLACK)
      point += C_POINT;
    if (node->board.box[B2] == BLACK)
      point += X_POINT;
  }

  if (node->board.box[H1] == BLACK)
    point -= CORNER_POINT;
  else if (node->board.box[H1] == EMPTY) {
    if (node->board.box[G1] == BLACK)
      point += C_POINT;
    if (node->board.box[H2] == BLACK)
      point += C_POINT;
    if (node->board.box[G2] == BLACK)
      point += X_POINT;
  }

  if (node->board.box[A8] == BLACK)
    point -= CORNER_POINT;
  else if (node->board.box[A8] == EMPTY) {
    if (node->board.box[B8] == BLACK)
      point += C_POINT;
    if (node->board.box[A7] == BLACK)
      point += C_POINT;
    if (node->board.box[B7] == BLACK)
      point += X_POINT;
  }

  if (node->board.box[H8] == BLACK)
    point -= CORNER_POINT;
  else if (node->board.box[H8] == EMPTY) {
    if (node->board.box[G8] == BLACK)
      point += C_POINT;
    if (node->board.box[H7] == BLACK)
      point += C_POINT;
    if (node->board.box[G7] == BLACK)
      point += X_POINT;
  }

  return point;
}

void Evaluator_evaluate(Node *node) {
  int available = available_point(node);

  if (available == INT_MAX) {
    // game over
    node->eval_point = (node->board.white > node->board.black) ? INT_MAX : -INT_MAX;
  } else {
    int important = important_point(node);
    node->eval_point = available + important;
  }
  if (node->next_color == BLACK)
    node->eval_point *= -1;
}

