#ifndef GAME_H
#define GAME_H

#include "board.h"

#define DIR_UP_LEFT     -10
#define DIR_UP          -9
#define DIR_UP_RIGHT    -8
#define DIR_LEFT        -1
#define DIR_RIGHT       1
#define DIR_DOWN_LEFT   8
#define DIR_DOWN        9
#define DIR_DOWN_RIGHT  10

typedef struct game Game;
struct game {
  //History history;
  int history;
  int (*set)(Game *this, Board *board, int x, int y);
  int (*set_by_str)(Game *this, Board *board, char str[]);
  int (*set_by_index)(Game *this, Board *board, int index);
  int (*can_set)(Game *this, Board *board, int x, int y);
  int (*can_pass)(Game *this, Board *board);
};

void Game_init(Game *game);
Game *Game_new(void);
void Game_delete(Game *game);

#endif
