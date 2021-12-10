#include <stdio.h>
#include "ai-reversi.h"
#include "board.h"


int main(void) {
  puts("\033[H\033[2J");
  puts("===== AI-reversi =====");
  puts("");

  Board *board = Board_new();

  board->print(board);

  return EXIT_OK;
}


