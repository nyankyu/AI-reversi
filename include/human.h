
#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

typedef struct human Human;
struct human {
  int color;
};

int Human_next(Player *player, Board *board);
void Human_delete(Player *player);
Player *Human_make_player(int color);

#endif
