#include <stdlib.h>
#include "ai-reversi.h"
#include "tree.h"

static void build_children(Node *node, int color, int depth) {
  if (node->depth > depth)
    return;
  node->children[0] = Node_new(node->board, color, node->depth + 1);
  build_children(node->children[0], color, depth);
  node->children[1] = Node_new(node->board, color, node->depth + 1);
  build_children(node->children[1], color, depth);
}

Tree *Tree_new(Board *board, int color, int depth) {
  Tree *tree = malloc(sizeof(Tree));
  if (tree == NULL) {
    exit(EXIT_ERR);
  }

  tree->root = Node_new(board, color, 0);
  tree->color = color;
  build_children(tree->root, color, depth);

  return tree;
}

void Tree_delete(Tree *tree) {
  free(tree);
}
