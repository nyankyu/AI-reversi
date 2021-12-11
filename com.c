#include <stdio.h>
#include <stdlib.h>
#include "com.h"
#include "ai-reversi.h"

static int next(Com *this, Board *board, int *eval_val) {
  if (this->color)
    *eval_val = board->box[0];
  return 0;
}

Com *Com_new(int color) {
  Com *com = malloc(sizeof(Com));
  if (com == NULL) {
    printf("ERROR: filus malloc() Com\n");
    exit(EXIT_ERR);
  }
  com->color = color;
  com->next = next;

  return com;
}

void Com_delete(Com *com) {
  free(com);
}
