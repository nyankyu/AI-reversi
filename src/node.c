#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ai-reversi.h"
#include "node.h"

Node *Node_new(Board *board, int next_color, int depth, int x, int y) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    exit(EXIT_ERR);
  }

  node->board = board;
  node->next_color = next_color;
  node->depth = depth;
  node->last_x = x;
  node->last_y = y;
  node->next_x = 0;
  node->next_y = 0;
  node->eval_point = INT_MAX;
  memset(node->children, 0, sizeof(Node *) * CHL_SIZE);

  return node;
}

void Node_delete(Node *node) {
  for (int i = 0; node->children[i]; i++)
    Node_delete(node->children[i]);
  Board_delete(node->board);
  free(node);
}
