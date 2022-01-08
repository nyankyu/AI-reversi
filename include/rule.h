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

int Rule_set(Board *board, int x, int y, int color);
int Rule_set_by_str(Board *board, const char str[], int color);
int Rule_can_set(const Board *board, int x, int y, int color);
int Rule_can_pass(const Board *board, int color);
int Rule_other_color(int color);

#endif
