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
#define B1  11
#define C1  12
#define D1  13
#define E1  14
#define F1  15
#define G1  16
#define H1  17

#define A2  19
#define B2  20
#define C2  21
#define D2  22
#define E2  23
#define F2  24
#define G2  25
#define H2  26

#define A3  28
#define B3  29
#define C3  30
#define D3  31
#define E3  32
#define F3  33
#define G3  34
#define H3  35

#define A4  37
#define B4  38
#define C4  39
#define D4  40
#define E4  41
#define F4  42
#define G4  43
#define H4  44

#define A5  46
#define B5  47
#define C5  48
#define D5  49
#define E5  50
#define F5  51
#define G5  52
#define H5  53

#define A6  55
#define B6  56
#define C6  57
#define D6  58
#define E6  59
#define F6  60
#define G6  61
#define H6  62

#define A7  64
#define B7  65
#define C7  66
#define D7  67
#define E7  68
#define F7  69
#define G7  70
#define H7  71

#define A8  73
#define B8  74
#define C8  75
#define D8  76
#define E8  77
#define F8  78
#define G8  79
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
void Board_init(Board *board);
void Board_rewrite(Board *dest, const Board *src);

#endif
