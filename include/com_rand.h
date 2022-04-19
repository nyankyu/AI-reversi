#ifndef COM_RAND_H
#define COM_RAND_H

#include "board.h"
#include "player.h"

typedef struct com_rand Com_rand;
struct com_rand {
  int color;
};

int Com_rand_next(Player *player, Board *board);
Player *Com_rand_make_player(int color);

#endif