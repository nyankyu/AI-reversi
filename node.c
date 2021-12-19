#include <stdlib.h>
#include <string.h>
#include "ai-reversi.h"
#include "node.h"

Node *Node_new(Board *board, int color, int depth) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    exit(EXIT_ERR);
  }

  node->board = Board_copy(board);
  node->color = color;
  node->depth = depth;
  memset(node->children, 0, sizeof(Node *) * CHIL_SIZE);

  return node;
}

#include "stdio.h"
void Node_delete(Node *node) {
  for (int i = 0; node->children[i]; i++)
    Node_delete(node->children[i]);
  Board_delete(node->board);
  free(node);
}
