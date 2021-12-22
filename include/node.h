#ifndef NODE_H
#define NODE_H

#include "board.h"

#define CHL_SIZE (BOARD_SIZE * BOARD_SIZE - 4)

typedef struct node Node;
struct node {
  Board *board;
  int color;
  int depth;
  Node *children[CHL_SIZE];
};

Node *Node_new(Board *board, int color, int depth);
void Node_delete(Node *node);

#endif