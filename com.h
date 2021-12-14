#ifndef COM_H
#define COM_H

#include "board.h"
#include "rule.h"

typedef struct com Com;
struct com {
  int color;
  Rule *rule;
  int (*next)(Com *this, Board *board, int *eval_val);
};

Com *Com_new(Rule *rule, int color);
void Com_delete(Com *com);

#endif
