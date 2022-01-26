#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "node.h"
#include "ai-reversi.h"

#define NODE_POOL_ARRAY_SIZE 2000

typedef struct list_elem ListElem;
struct list_elem {
  Node array[NODE_POOL_ARRAY_SIZE];
  ListElem *next;
};

static ListElem *g_nodePoolTop = NULL;
static ListElem *g_currentArray;
static int g_index;

static inline void extendPool(void) {
  ListElem *elem = malloc(sizeof(ListElem));
  if (elem == NULL) {
    fprintf(stderr, "FAILURE: make new pool. malloc()\n");
    exit(EXIT_FAILURE);
  }

  elem->next = NULL;
  g_currentArray->next = elem;
}

static inline void incrementIndex(void) {
  g_index++;
  if (g_index != NODE_POOL_ARRAY_SIZE)
    return;

  g_index = 0;

  if (g_currentArray->next == NULL) {
    extendPool();
  }
  g_currentArray = g_currentArray->next;
}

Node *Node_new(const Board *board, int next_color, int depth, int x, int y) {
  incrementIndex();
  Node *node = &g_currentArray->array[g_index];

  Board_rewrite(&node->board ,board);
  node->next_color = next_color;
  node->depth = depth;
  node->last_x = x;
  node->last_y = y;
  node->next_x = 0;
  node->next_y = 0;
  node->eval_point = INT_MAX;
  node->pass = FALSE;
  memset(node->children, 0, sizeof(Node *) * CHL_SIZE);

  return node;
}

void Node_deletePool(void) {
  ListElem *elem = g_nodePoolTop;
  while (elem != NULL) {
    ListElem *next = elem->next;
    free(elem);
    elem = next;
  }
  g_currentArray = NULL;
  g_nodePoolTop = NULL;
  g_index = -1;
}

void Node_initPool(void) {
  if (g_nodePoolTop == NULL) {
    g_nodePoolTop = malloc(sizeof(ListElem));
    if (g_nodePoolTop == NULL) {
      fprintf(stderr, "FAILURE: make new pool. malloc()\n");
      exit(EXIT_FAILURE);
    }
    g_nodePoolTop->next = NULL;
  }

  g_currentArray = g_nodePoolTop;
  g_index = -1;
}