#ifndef TREE_H
#define TREE_H

#include "board.h"
#include "com.h"


typedef struct tree Tree;
struct tree {
  Node *root;
};

Tree *Tree_new(Com *com, const Board *board, int max_depth);
void Tree_delete(Tree *tree);

#endif
