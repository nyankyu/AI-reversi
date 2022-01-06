#ifndef TREE_H
#define TREE_H

#include "board.h"
#include "node.h"
#include "com.h"


typedef struct tree Tree;
struct tree {
  void (*get_next_point)(Tree *tree, int *x, int *y);
  Node *root;
  int my_color;
};

Tree *Tree_new(Com *com, Board *board, int my_color, int max_depth);
void Tree_delete(Tree *tree);

#endif
