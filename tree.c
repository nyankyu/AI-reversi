#include <stdlib.h>
#include "ai-reversi.h"
#include "tree.h"

static void build_children(Node *node, int color, int max_depth) {
  if (node->depth > max_depth)
    return;

  int child_index = 0;
  Board *board = NULL;
  int count;
  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (board == NULL)
        board = Board_copy(node->board);
      count = g_rule->set(board, x, y, color);
      if (count == 0)
        continue;

      node->children[child_index] = Node_new(board, color, node->depth + 1);
      board = NULL;
      build_children(node->children[child_index], color, max_depth);
      child_index++;
      if (child_index > 1)
        break;
    }
  }
}

Tree *Tree_new(Board *board, int my_color, int max_depth) {
  Tree *tree = malloc(sizeof(Tree));
  if (tree == NULL) {
    exit(EXIT_ERR);
  }

  tree->root = Node_new(board, my_color, 0);
  tree->my_color = my_color;
  build_children(tree->root, my_color, max_depth);

  return tree;
}

void Tree_delete(Tree *tree) {
  Node_delete(tree->root);
  free(tree);
}
