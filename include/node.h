#ifndef NODE_H
#define NODE_H

#include "board.h"

#define CHL_SIZE (BOARD_SIZE * BOARD_SIZE - 4)

/*
 * (pool size) = (col size) * (row size)
 * depth | node size
 * 4     |    100_000
 * 5     | 12_000_000
 * 6     | 40_000_000
 */
#define NODE_POOL_COL_SIZE 2000
#define NODE_POOL_ROW_SIZE 6000

typedef struct node Node;
struct node {
  Board board;
  int next_color;
  int depth;
  int eval_point;
  int last_x;
  int last_y;
  int next_x;
  int next_y;
  int pass;
  Node *children[CHL_SIZE];
};

Node *Node_new(const Board *board, int next_color, int depth, int x, int y);
void Node_deletePool(void);
void Node_initPool(void);

#endif
