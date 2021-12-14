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
  //History history;
  int history;
  int (*set)(Board *board, int x, int y);
  int (*set_by_str)(Board *board, char str[]);
  int (*set_by_index)(Board *board, int index);
  int (*can_set)(Board *board, int x, int y);
  int (*can_pass)(Board *board);
};

void Rule_init(Rule *rule);
Rule *Rule_new(void);
void Rule_delete(Rule *rule);

#endif
