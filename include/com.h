#ifndef COM_H
#define COM_H

#include "player.h"

#define DEPTH_MAX 6
#define COM_PASS 100

extern int g_print;

typedef struct {
  int x;
  int y;
} Point;

Player *Com_make_player(int color);

#endif
