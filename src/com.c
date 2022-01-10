#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "com.h"
#include "ai-reversi.h"
#include "tree.h"

void Com_next(Com *self,const Board *board, int *x, int *y, int *eval_val) {
  Board *copy = Board_copy(board);
  Tree *tree = Tree_new(self, copy, 5);

  *x = tree->root->next_x;
  *y = tree->root->next_y;
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

  return com;
}

void Com_delete(Com *com) {
  free(com);
}
