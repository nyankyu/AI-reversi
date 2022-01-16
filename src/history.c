#include <stdlib.h>
#include <memory.h>
#include "history.h"

void History_add(History *history, const Board *board, int next_color) {
  if (history->current == BOARD_SIZE * BOARD_SIZE - 1)
    return;

  history->current++;

  Board_rewrite(&history->board_array[history->current], board);
  history->next_color = next_color;
}

void History_undo(History *history, Board *current) {
  if (history->current == 0)
    return;
  history->current--;
  Board_rewrite(current, &history->board_array[history->current]);
}

void History_init(History *history) {
  history->current = -1;
}
