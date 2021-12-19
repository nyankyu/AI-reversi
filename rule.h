#ifndef RULE_H
#define RULE_H

#include "board.h"

#define DIR_UP_LEFT     -10
#define DIR_UP          -9
#define DIR_UP_RIGHT    -8
#define DIR_LEFT        -1
#define DIR_RIGHT       1
#define DIR_DOWN_LEFT   8
#define DIR_DOWN        9
#define DIR_DOWN_RIGHT  10

typedef struct rule Rule;
struct rule {
  int (*set)(Board *board, int x, int y, int color);
  int (*set_by_str)(Board *board, char str[], int color);
  int (*set_by_index)(Board *board, int index, int color);
  int (*can_set)(Board *board, int x, int y, int color);
  int (*can_pass)(Board *board, int color);
  int (*other_color)(int color);
};

void Rule_init(Rule *rule);
Rule *Rule_new(void);
void Rule_delete(Rule *rule);

#endif
