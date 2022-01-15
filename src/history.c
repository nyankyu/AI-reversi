#include <stdlib.h>
#include <memory.h>
#include "history.h"

void History_add(History *history, const Board *board, int next_color) {
  if (history->current == BOARD_SIZE * BOARD_SIZE - 1)
    return;

  history->current++;

  Board *copy = Board_copy(board);
  history->board_array[history->current] = copy;
  history->next_color = next_color;
}

void History_undo(History *history) {
  if (history->current == 0)
    return;
  history->current--;
}

History *History_new(void) {
  History *history = malloc(sizeof(History));
  if (history == NULL)
    exit(EXIT_FAILURE);
  memset(history->board_array, 0, sizeof(Board *) * BOARD_SIZE * BOARD_SIZE);
  history->current = -1;
  return history;
}

void History_delete(History *history) {
  for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
    Board_delete(history->board_array[i]);
  }
  free(history);
  history = NULL;
}
