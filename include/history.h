#ifndef HISTORY_H
#define HISTORY_H

#include "board.h"

typedef struct history {
  Board board_array[BOARD_SIZE * BOARD_SIZE];
  int current;
  int next_color;
} History;

void History_add(History *history, const Board *board, int next_color);
void History_undo(History *history, Board *current);
void History_init(History *history);

#endif
