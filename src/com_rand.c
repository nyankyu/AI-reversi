#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "com_rand.h"
#include "ai-reversi.h"
#include "player.h"

int Com_rand_next(Player *player, Board *board) {
  int x_array[BOARD_SIZE * BOARD_SIZE];
  int y_array[BOARD_SIZE * BOARD_SIZE];
  int index = 0;

  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (Rule_can_set(board, x, y, player->color) == NG)
        continue;
      x_array[index] = x;
      y_array[index] = y;
      index++;
    }
  }

  if (index == 0) {
    if (g_print) printf("PASS\n");
    return PLAYER_PASS;
  }

  int r = rand() % index;
  Rule_set(board, x_array[r], y_array[r], player->color);
  if (g_print) printf("%c%c\n", 'a' + x_array[r] - 1, '1' + y_array[r] - 1);

  return PLAYER_PUT;
}

Player *Com_rand_make_player(int color) {
  srand((unsigned int)time(NULL));

  Player *player = malloc(sizeof(Player));
  if (player == NULL)
    exit(EXIT_FAILURE);

  player->color = color;
  player->name = "Com-Random";
  player->put_next = Com_rand_next;
  return player;
}

