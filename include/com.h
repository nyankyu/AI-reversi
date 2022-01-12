#ifndef COM_H
#define COM_H

#include "board.h"
#include "player.h"

typedef struct com Com;
struct com {
  int color;
};

int Com_next(Player *player, Board *board);
void Com_delete(Player *player);
Player *Com_make_player(int color);

#endif
