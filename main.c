#include <stdio.h>
#include "ai-reversi.h"
#include "board.h"


int main(void) {
  puts("\033[H\033[2J");
  puts("===== AI-reversi =====");
  puts("");

  Board *board = Board_new();
  board->set_box(board, 6, 4, WHITE);
  board->reverse(board, 5, 4);
  board->print(board);

  Board_delete(board);

  return EXIT_OK;
}


