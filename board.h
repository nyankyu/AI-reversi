#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE  8
#define BOX_SIZE    ((BOARD_SIZE + 1) * (BOARD_SIZE + 2) + 1)

#define EMPTY 0
#define WHITE 1
#define BLACK 2
#define WALL  3

typedef struct board Board;

typedef struct board {
  int box[BOX_SIZE];
  void (*print)(Board *this);
  void (*set_box)(Board *this, int x, int y, int v);
  void (*reverse)(Board *this, int x, int y);
} Board;

void  Board_init(Board *board);
Board *Board_new(void);
void  Board_delete(Board *board);

#endif
