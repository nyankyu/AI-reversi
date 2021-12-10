#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE  8
#define BOX_SIZE    ((BOARD_SIZE + 1) * (BOARD_SIZE + 2) + 1)

#define EMPTY 0
#define WHITE 1
#define BRACK 2
#define WALL  3

typedef struct board Board;
void  Board_init(Board *board);

typedef struct board {
  int box[BOX_SIZE];
  void (*print)(Board *this);
} Board;

#endif
