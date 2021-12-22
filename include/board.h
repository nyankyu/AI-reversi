#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE  8
#define BOX_SIZE    ((BOARD_SIZE + 1) * (BOARD_SIZE + 2) + 1)

#define EMPTY 0
#define WHITE 1
#define BLACK 2
#define WALL  3

#define DIR_UP_LEFT     -10
#define DIR_UP          -9
#define DIR_UP_RIGHT    -8
#define DIR_LEFT        -1
#define DIR_RIGHT       1
#define DIR_DOWN_LEFT   8
#define DIR_DOWN        9
#define DIR_DOWN_RIGHT  10

#define POS(x,y) ((BOARD_SIZE + 1) * y + x)

typedef struct board Board;

struct board {
  int empty;
  int white;
  int black;
  int box[BOX_SIZE];
  void (*print)(const Board *self);
};

void  Board_init(Board *board);
Board *Board_new(void);
void  Board_delete(Board *board);
Board *Board_copy(const Board *board);

#endif
