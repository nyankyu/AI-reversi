#ifndef COM_H
#define COM_H

#include "player.h"

#define DEPTH_MAX 5
#define COM_PASS 100

extern int g_print;

Player *Com_make_player(int color);

#endif
