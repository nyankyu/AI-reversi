#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "human.h"
#include "ai-reversi.h"

#define BUFF_SIZE 256

static inline void get_input(char buff[]) {
  if (fgets(buff, BUFF_SIZE, stdin) == NULL) {
    exit(EXIT_FAILURE);
  }
  char *p = strchr(buff, '\n');
  if (p != NULL)
    *p = '\0';
}

int Human_next(Player *player, Board *board) {
  if (Rule_can_pass(board, player->color) == OK)
    return PLAYER_PASS;

  char buff[BUFF_SIZE];
  get_input(buff);
  if (strcmp(buff, "q") == 0)
    return PLAYER_QUIT;
  if (strcmp(buff, "r") == 0)
    return PLAYER_UNDO;

  if (Rule_set_by_str(board, buff, player->color) == 0)
    return PLAYER_NG;
  return PLAYER_PUT;
}

Player *Human_make_player(int color) {
  Player *player = malloc(sizeof(Player));
  if (player == NULL)
    exit(EXIT_FAILURE);

  player->color = color;
  player->put_next = Human_next;

  return player;
}