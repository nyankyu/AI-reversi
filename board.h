#ifndef BOARD_H
#define BOARD_H

typedef struct board Board;
void  Board_init(Board *board);

typedef struct board {
  void (*print)(void);
} Board;

#endif
