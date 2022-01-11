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

#define A1  10
#define A2  11
#define A3  12
#define A4  13
#define A5  14
#define A6  15
#define A7  16
#define A8  17

#define B1  19
#define B2  20
#define B3  21
#define B4  22
#define B5  23
#define B6  24
#define B7  25
#define B8  26

#define C1  28
#define C2  29
#define C3  30
#define C4  31
#define C5  32
#define C6  33
#define C7  34
#define C8  35

#define D1  37
#define D2  38
#define D3  39
#define D4  40
#define D5  41
#define D6  42
#define D7  43
#define D8  44

#define E1  46
#define E2  47
#define E3  48
#define E4  49
#define E5  50
#define E6  51
#define E7  52
#define E8  53

#define F1  55
#define F2  56
#define F3  57
#define F4  58
#define F5  59
#define F6  60
#define F7  61
#define F8  62

#define G1  64
#define G2  65
#define G3  66
#define G4  67
#define G5  68
#define G6  69
#define G7  70
#define G8  71

#define H1  73
#define H2  74
#define H3  75
#define H4  76
#define H5  77
#define H6  78
#define H7  79
#define H8  80

#define POS(x,y) ((BOARD_SIZE + 1) * y + x)

typedef struct board Board;

struct board {
  int empty;
  int white;
  int black;
  int box[BOX_SIZE];
};

void Board_print(const Board *self);
void Board_make_box(Board *self, const char str[]);
void  Board_init(Board *board);
Board *Board_new(void);
void  Board_delete(Board *board);
Board *Board_copy(const Board *board);
void Board_rewrite(Board *dest, const Board *src);

#endif
