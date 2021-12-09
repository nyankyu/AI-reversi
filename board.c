#include <stdio.h>
#include "board.h"

void  print(void) {
  puts("   A B C D E F G H");
  puts(" 1 . . . . . . . .");
  puts(" 2 . . . . . . . .");
  puts(" 3 . . . . . . . .");
  puts(" 4 . . . O X . . .");
  puts(" 5 . . . X O . . .");
  puts(" 6 . . . . . . . .");
  puts(" 7 . . . . . . . .");
  puts(" 8 . . . . . . . .");
}

void  Board_init(Board *board) {
  board->print = print;
}
