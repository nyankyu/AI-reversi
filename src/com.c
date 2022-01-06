#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "com.h"
#include "ai-reversi.h"
#include "tree.h"

static void next(Com *self,const Board *board, int *x, int *y, int *eval_val) {
  Board *copy = Board_copy(board);
  Tree *tree = Tree_new(self, copy, self->color, 3);

  tree->get_next_point(tree, x, y);
  if (*x != 0)
    *eval_val = tree->root->eval_point;
  Tree_delete(tree);
}

Com *Com_new(int color) {
  Com *com = malloc(sizeof(Com));
  if (com == NULL) {
    printf("ERROR: files malloc() Com\n");
    exit(EXIT_ERR);
  }
  com->color = color;
  com->next = next;

  return com;
}

void Com_delete(Com *com) {
  free(com);
}
