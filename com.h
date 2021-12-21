#ifndef COM_H
#define COM_H

#include "board.h"

typedef struct com Com;
struct com {
  int color;
  int (*next)(Com *this, const Board *board, int *eval_val);
};

Com *Com_new(int color);
void Com_delete(Com *com);

#endif
