
#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

#define PLAYER_PASS 10
#define PLAYER_UNDO 11
#define PLAYER_QUIT 12
#define PLAYER_PUT  13
#define PLAYER_ERR  14
#define PLAYER_NG   15

typedef struct player Player;
struct player {
  int color;
  void *obj;
  int (*next)(Player *player, Board *board);
  void (*Player_delete)(Player *player);
};

#endif
