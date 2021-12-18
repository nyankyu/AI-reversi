#ifndef TREE_H
#define TREE_H

#include "board.h"
#include "node.h"


typedef struct tree Tree;
struct tree {
  Node *root;
  int my_color;
};

Tree *Tree_new(Board *board, int my_color, int max_depth);
void Tree_delete(Tree *tree);

#endif
