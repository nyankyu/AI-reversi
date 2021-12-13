#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "com.h"
#include "ai-reversi.h"
#include "game.h"

static int next(Com *this, Game *game, Board *board, int *eval_val) {
  if (this == NULL)
    return 0;
  *eval_val = 0;
  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (game->can_set(game, board, x, y) == OK)
          return 9 * y + x;
    }
  }
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
