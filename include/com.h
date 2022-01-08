#ifndef COM_H
#define COM_H

#include "board.h"

typedef struct com Com;
struct com {
  int color;
};

void Com_next(Com *self, const Board *board, int *x, int *y, int *eval_val);
Com *Com_new(int color);
void Com_delete(Com *com);

#endif
