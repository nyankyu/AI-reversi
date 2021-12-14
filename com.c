#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "com.h"
#include "ai-reversi.h"
#include "rule.h"

static int next(Com *this, Board *board, int *eval_val) {
  *eval_val = 0;
  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (this->rule->can_set(board, x, y) == OK)
          return 9 * y + x;
    }
  }
  return 0;
}

Com *Com_new(Rule *rule, int color) {
  Com *com = malloc(sizeof(Com));
  if (com == NULL) {
    printf("ERROR: filus malloc() Com\n");
    exit(EXIT_ERR);
  }
  com->rule = rule;
  com->color = color;
  com->next = next;

  return com;
}

void Com_delete(Com *com) {
  if (com->rule != NULL) {
    free(com->rule);
    com->rule = NULL;
  }
  free(com);
}
