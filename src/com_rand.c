#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "com_rand.h"
#include "ai-reversi.h"
#include "player.h"

inline int Com_rand_next(Player *player, Board *board) {
  int x_array[BOARD_SIZE * BOARD_SIZE];
  int y_array[BOARD_SIZE * BOARD_SIZE];
  size_t index = 0;

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

static inline Com_rand *Com_rand_new(int color) {
  Com_rand *com_rand = malloc(sizeof(Com_rand));
  if (com_rand == NULL) {
    printf("ERROR: files malloc() Com_rand\n");
    exit(EXIT_FAILURE);
  }
  com_rand->color = color;

  return com_rand;
}

inline void Com_rand_delete(Player *player) {
  free(player->obj);
  free(player);
}

inline Player *Com_rand_make_player(int color) {
  srand((unsigned int)time(NULL));

  Com_rand *com_rand = Com_rand_new(color);
  Player *player = malloc(sizeof(Player));
  if (player == NULL)
    exit(EXIT_FAILURE);

  player->color = color;
  player->name = "Com-Random";
  player->next = Com_rand_next;
  player->Player_delete = Com_rand_delete;
  player->obj = com_rand;
  return player;
}

