#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "node.h"

Node **g_nodePool = NULL;
int g_nodePoolCol;
int g_nodePoolRow;
int g_nodePoolMax;

static void makePool(void) {
  g_nodePool = malloc(sizeof(Node *) * NODE_POOL_ROW_SIZE);
  if (g_nodePool == NULL) {
    fprintf(stderr, "FAILURE: make new pool. malloc()\n");
    exit(EXIT_FAILURE);
  }
  for (int row = 0; row < NODE_POOL_ROW_SIZE; row++) {
    g_nodePool[row] = malloc(sizeof(Node) * NODE_POOL_COL_SIZE);
    if (g_nodePool[row] == NULL) {
      fprintf(stderr, "FAILURE: make new pool. malloc()\n");
      exit(EXIT_FAILURE);
    }
  }
}

void incrementIndex(void) {
  g_nodePoolCol++;
  if (g_nodePoolCol == NODE_POOL_COL_SIZE) {
    g_nodePoolRow++;
    g_nodePoolCol = 0;
  }
}

Node *Node_new(const Board *board, int next_color, int depth, int x, int y) {
  if (g_nodePoolRow == NODE_POOL_ROW_SIZE) {
    fprintf(stderr, "FAILURE: ran out of Node pool\n");
    exit(EXIT_FAILURE);
  }
  if (g_nodePool == NULL)
    makePool();

  Node *node = &g_nodePool[g_nodePoolRow][g_nodePoolCol];
  incrementIndex();

  Board_rewrite(&node->board ,board);
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

void Node_deletePool(void) {
  if (g_nodePool == NULL)
    return;
  for (int row = 0; row < NODE_POOL_ROW_SIZE; row++) {
    free(g_nodePool[row]);
  }
  free(g_nodePool);
  g_nodePool = NULL;
  Node_initPool();

  //printf("use pool; %d\n", g_nodePoolMax);
}

void Node_initPool(void) {
  int count = g_nodePoolRow * NODE_POOL_COL_SIZE + g_nodePoolCol;
  if (g_nodePoolMax < count)
    g_nodePoolMax = count;
  g_nodePoolRow = 0;
  g_nodePoolCol = 0;
}
