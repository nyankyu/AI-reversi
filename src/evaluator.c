#include <limits.h>
#include "evaluator.h"
#include "rule.h"
#include "ai-reversi.h"

int available_point(Node *node) {
  int count = 0;

  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (Rule_can_set(node->board, x, y, WHITE) == OK) {
        if (node->next_color == WHITE)
          count++;
        else
          count--;
      }
    }
  }
  return count;
}

int important_point(Node *node) {
  int count = 0;

  if (node->board->box[A1] == WHITE)
    count += 60;
  if (node->board->box[A1] == BLACK)
    count -= 60;
  if (node->board->box[H1] == WHITE)
    count += 60;
  if (node->board->box[H1] == BLACK)
    count -= 60;
  if (node->board->box[A8] == WHITE)
    count += 60;
  if (node->board->box[A8] == BLACK)
    count -= 60;
  if (node->board->box[H8] == WHITE)
    count += 60;
  if (node->board->box[H8] == BLACK)
    count -= 60;

  if (node->board->box[B1] == WHITE)
    count += 30;
  if (node->board->box[B1] == BLACK)
    count -= 30;
  if (node->board->box[G1] == WHITE)
    count += 30;
  if (node->board->box[G1] == BLACK)
    count -= 30;
  if (node->board->box[A2] == WHITE)
    count += 30;
  if (node->board->box[A2] == BLACK)
    count -= 30;
  if (node->board->box[H2] == WHITE)
    count += 30;
  if (node->board->box[H2] == BLACK)
    count -= 30;
  if (node->board->box[A7] == WHITE)
    count += 30;
  if (node->board->box[A7] == BLACK)
    count -= 30;
  if (node->board->box[H7] == WHITE)
    count += 30;
  if (node->board->box[H7] == BLACK)
    count -= 30;
  if (node->board->box[B8] == WHITE)
    count += 30;
  if (node->board->box[B8] == BLACK)
    count -= 30;
  if (node->board->box[G8] == WHITE)
    count += 30;
  if (node->board->box[G8] == BLACK)
    count -= 30;

  if (node->board->box[B2] == WHITE)
    count += 60;
  if (node->board->box[B2] == BLACK)
    count -= 60;
  if (node->board->box[G2] == WHITE)
    count += 60;
  if (node->board->box[G2] == BLACK)
    count -= 60;
  if (node->board->box[B7] == WHITE)
    count += 60;
  if (node->board->box[B7] == BLACK)
    count -= 60;
  if (node->board->box[G7] == WHITE)
    count += 60;
  if (node->board->box[G7] == BLACK)
    count -= 60;

  return count;
}

void Evaluator_evaluate(Node *node, int my_color) {
  int available = available_point(node);

  if (available == 0) {
    node->eval_point = (node->board->white > node->board->black) ? INT_MAX : -INT_MAX;
    if (my_color == BLACK)
      node->eval_point *= -1;
    return;
  }

  int important = important_point(node);
  node->eval_point = available + important;
  if (node->next_color == BLACK)
    node->eval_point *= -1;
  if (my_color != node->next_color)
    node->eval_point *= -1;
}

