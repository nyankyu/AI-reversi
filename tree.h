#ifndef TREE_H
#define TREE_H

#include "board.h"
#include "node.h"


typedef struct tree Tree;
struct tree {
  Node *root;
  int color;
};

Tree *Tree_new(Board *board, int color, int depth);
void Tree_delete(Tree *tree);

#endif
