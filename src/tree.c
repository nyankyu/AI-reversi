#include <stdlib.h>
#include <limits.h>
#include "ai-reversi.h"
#include "tree.h"
#include "com.h"
#include "evaluator.h"

static inline void set_eval_point(Node *node) {
  for (Node **child = node->children; *child != NULL; child++) {
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
    Evaluator_evaluate(node, com->color);
    return;
  }

  Board board;
  Board_rewrite(&board,&node->board);
  Node **children = node->children;

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

  if (children == node->children) {
    // pass
    if (node->pass == TRUE) {
      // game over
      if (node->board.white > node->board.black && com->color == WHITE)
        node->eval_point = INT_MAX;
      else if (node->board.white < node->board.black && com->color == BLACK)
        node->eval_point = INT_MAX;
      else
        node->eval_point = -INT_MAX;

      return;
    }
    *children = Node_new(&board, node->next_color, node->depth + 1, node->last_x, node->last_y);
    (*children)->pass = TRUE;
    build_children(com, *children, max_depth);
  }

  set_eval_point(node);
}

Tree *Tree_new(Com *com, const Board *board, int max_depth) {
  Tree *tree = malloc(sizeof(Tree));
  if (tree == NULL) {
    exit(EXIT_FAILURE);
  }

  Node_initPool();
  tree->root = Node_new(board, com->color, 0, 0, 0);
  build_children(com, tree->root, max_depth);
  return tree;
}

void Tree_delete(Tree *tree) {
  free(tree);
}
