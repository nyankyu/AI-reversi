#include "evaluator.h"
#include "rule.h"
#include "ai-reversi.h"

static inline int available_point(Node *node) {
  int count = 0;

  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (Rule_can_set(&node->board, x, y, node->next_color) == OK) {
        count++;
      }
    }
  }
  return count;
}

static inline int important_point(Node *node) {
  int point = 0;
  int other_color = Rule_other_color(node->next_color);

  if (node->board.box[A1] == node->next_color)
    point += CORNER_POINT;
  else if (node->board.box[A1] == other_color)
    point -= CORNER_POINT;
  else {
    if (node->board.box[B1] == node->next_color)
      point -= C_POINT;
    if (node->board.box[A2] == node->next_color)
      point -= C_POINT;
    if (node->board.box[B2] == node->next_color)
      point -= X_POINT;
  }

  if (node->board.box[H1] == node->next_color)
    point += CORNER_POINT;
  else if (node->board.box[H1] == other_color)
    point -= CORNER_POINT;
  else {
    if (node->board.box[G1] == node->next_color)
      point -= C_POINT;
    if (node->board.box[H2] == node->next_color)
      point -= C_POINT;
    if (node->board.box[G2] == node->next_color)
      point -= X_POINT;
  }

  if (node->board.box[A8] == node->next_color)
    point += CORNER_POINT;
  else if (node->board.box[A8] == other_color)
    point -= CORNER_POINT;
  else {
    if (node->board.box[B8] == node->next_color)
      point -= C_POINT;
    if (node->board.box[A7] == node->next_color)
      point -= C_POINT;
    if (node->board.box[B7] == node->next_color)
      point -= X_POINT;
  }

  if (node->board.box[H8] == node->next_color)
    point += CORNER_POINT;
  else if (node->board.box[H8] == other_color)
    point -= CORNER_POINT;
  else {
    if (node->board.box[G8] == node->next_color)
      point -= C_POINT;
    if (node->board.box[H7] == node->next_color)
      point -= C_POINT;
    if (node->board.box[G7] == node->next_color)
      point -= X_POINT;
  }

  return point;
}

void Evaluator_evaluate(Node *node, int my_color) {
  int available = available_point(node);
  int important = important_point(node);
  node->eval_point = available + important;
  if (node->next_color != my_color)
    node->eval_point *= -1;
}

