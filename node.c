#include <stdlib.h>
#include <string.h>
#include "ai-reversi.h"
#include "node.h"

Node *Node_new(Board *board, int color, int depth) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    exit(EXIT_ERR);
  }

  node->board = board;
  node->color = color;
  node->depth = depth;
  memset(node->children, 0, CHIL_SIZE);

  return node;
}

void Node_delete(Node *node) {
  Board_delete(node->board);
  free(node);
}
