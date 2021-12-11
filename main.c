#include <stdio.h>
#include "ai-reversi.h"
#include "board.h"


int main(void) {
  puts("\033[H\033[2J");
  puts("===== AI-reversi =====");
  puts("");

  Board *board = Board_new();
  board->set(board, 6, 4, WHITE);
  board->set(board, 4, 3, BLACK);
  //board->set(board, 7, 4, BLACK);
  //board->set(board, 6, 6, BLACK);
  //board->set(board, 3, 2, WHITE);
  //board->set(board, 3, 5, WHITE);
  //board->set(board, 6, 7, WHITE);
  //board->set(board, 6, 3, WHITE);
  //board->set(board, 6, 5, WHITE);
  board->print(board);

  for (int y = 1; y <= 8 ; y++) {
    printf("   ");
    for (int x = 1; x <= 8 ; x++) {
      if (board->can_set(board, x, y, BLACK) == OK) {
        printf("O ");
      } else {
        printf("X ");
      }
    }
    printf("\n");
  }

  Board_delete(board);

  return EXIT_OK;
}


