#ifndef NODE_H
#define NODE_H

#include "board.h"

#define CHL_SIZE (BOARD_SIZE * BOARD_SIZE - 4)
#define NODE_POOL_SIZE 10000000

typedef struct node Node;
struct node {
  Board *board;
  int next_color;
  int depth;
  int eval_point;
  int last_x;
  int last_y;
  int next_x;
  int next_y;
  Node *children[CHL_SIZE];
};

Node *Node_new(Board *board, int next_color, int depth, int x, int y);
void Node_delete(Node *node);

#endif
