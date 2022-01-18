#include <stdlib.h>
#include "ai-reversi.h"
#include "tree.h"
#include "com.h"
#include "evaluator.h"

static inline void set_eval_point(Node *node) {
  for (Node **child = &node->children[0]; *child != NULL; child++) {
    if (node->eval_point >= (*child)->eval_point) {
      node->eval_point = (*child)->eval_point;
      node->next_x = (*child)->last_x;
      node->next_y = (*child)->last_y;
    }
  }

  node->eval_point *= -1;
}

static inline void build_children(Com *com, Node *node, int max_depth) {
  if (node->depth >= max_depth) {
    Evaluator_evaluate(node);
    return;
  }

  Board board;
  Board_rewrite(&board,&node->board);
  Node **children = &node->children[0];

  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (Rule_set(&board, x, y, node->next_color) == 0)
        continue;
      *children = Node_new(&board, Rule_other_color(node->next_color), node->depth + 1, x, y);
      Board_rewrite(&board,&node->board);
      build_children(com, *children, max_depth);
      children++;
    }
  }

  if (children == &node->children[0]) {
    *children = Node_new(&board, node->next_color, node->depth + 1, node->last_x, node->last_y);
    build_children(com, *children, max_depth);
  }

  set_eval_point(node);
}

inline Tree *Tree_new(Com *com, const Board *board, int max_depth) {
  Tree *tree = malloc(sizeof(Tree));
  if (tree == NULL) {
    exit(EXIT_FAILURE);
  }

  tree->root = Node_new(board, com->color, 0, 0, 0);
  //tree->my_color = my_color;
  build_children(com, tree->root, max_depth);
  return tree;
}

inline void Tree_delete(Tree *tree) {
  Node_initPool();
  free(tree);
}
