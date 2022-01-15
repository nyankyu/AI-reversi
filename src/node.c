#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "node.h"

Node g_nodePool[NODE_POOL_SIZE];
int g_nodePoolIndex = 0;

Node *Node_new(Board *board, int next_color, int depth, int x, int y) {
  if (g_nodePoolIndex == NODE_POOL_SIZE) {
    fputs("Failure: Used up all the Node prepared in advance.\n", stderr);
    exit(EXIT_FAILURE);
  }
  Node *node = &g_nodePool[g_nodePoolIndex++];

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

/**
 * Release node. Do note perform free().
 * We only consider the number of new and delete operations,
 * but this implementation is fine because Node_delete() is
 * called at the same time when the program finishes using
 * all the nodes.
 * @param node
 */
void Node_delete(Node *node) {
  if (node == NULL)
    return;
  if (g_nodePoolIndex == 0)
    exit(EXIT_FAILURE);
  for (int i = 0; node->children[i]; i++)
    Node_delete(node->children[i]);
  Board_delete(node->board);
  g_nodePoolIndex--;
}
