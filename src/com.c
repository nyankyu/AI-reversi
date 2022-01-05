#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "com.h"
#include "ai-reversi.h"
#include "tree.h"

static int next(Com *self,const Board *board, int *eval_val) {
  // dummy use self
  if (self == NULL)
    exit(EXIT_ERR);


  Board *copy = Board_copy(board);
  Tree *tree = Tree_new(self, copy, self->color, 3);
  Tree_delete(tree);

  // most weak AI
  *eval_val = 0;
  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (g_rule->can_set(board, x, y, self->color) == OK)
          return 9 * y + x;
    }
  }
  return 0;
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
