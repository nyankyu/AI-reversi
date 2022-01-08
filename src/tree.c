#include <stdlib.h>
#include "ai-reversi.h"
#include "tree.h"
#include "com.h"
#include "evaluator.h"

static void set_eval_point(Node *node) {
  for (Node **child = &node->children[0]; *child != NULL; child++) {
    if (node->eval_point > (*child)->eval_point) {
      node->eval_point = (*child)->eval_point;
      node->next_x = (*child)->last_x;
      node->next_y = (*child)->last_y;
    }
  }

  node->eval_point *= -1;
}

static void build_children(Com *com, Node *node, int max_depth) {
  if (node->depth >= max_depth) {
    evaluate(node, com->color);
    return;
  }

  Board *board = Board_copy(node->board);
  Node **children = &node->children[0];

  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (g_rule->set(board, x, y, node->next_color) == 0)
        continue;
      *children = Node_new(board, g_rule->other_color(node->next_color), node->depth + 1, x, y);
      board = Board_copy(node->board);
      build_children(com, *children, max_depth);
      children++;
    }
  }

  if (children == &node->children[0]) {
    *children = Node_new(board, node->next_color, node->depth + 1, node->last_x, node->last_y);
    build_children(com, *children, max_depth);
  } else {
    Board_delete(board);
  }

  set_eval_point(node);
}

Tree *Tree_new(Com *com, Board *board, int my_color, int max_depth) {
  Tree *tree = malloc(sizeof(Tree));
  if (tree == NULL) {
    exit(EXIT_ERR);
  }

  tree->root = Node_new(board, my_color, 0, 0, 0);
  tree->my_color = my_color;
  build_children(com, tree->root, max_depth);
  return tree;
}

void Tree_delete(Tree *tree) {
  Node_delete(tree->root);
  free(tree);
}
