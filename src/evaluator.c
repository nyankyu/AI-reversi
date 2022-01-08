#include "evaluator.h"

void Evaluator_evaluate(Node *node, int my_color) {
  node->eval_point = (my_color == WHITE) ? node->board->black : node->board->white;
  if (my_color != node->next_color)
    node->eval_point *= -1;
}

