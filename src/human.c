#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "human.h"
#include "ai-reversi.h"

#define BUFF_SIZE 256

static void get_input(char buff[]) {
  if (fgets(buff, BUFF_SIZE, stdin) == NULL) {
    exit(EXIT_ERR);
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

Human *Human_new(int color) {
  Human *human = malloc(sizeof(Human));
  if (human == NULL)
    exit(EXIT_ERR);
  human->color = color;
  return human;
}

void Human_delete(Player *player) {
  free(player->obj);
  free(player);
}

Player *Human_make_player(int color) {
  Human *human = Human_new(color);
  Player *player = malloc(sizeof(Player));
  if (player == NULL)
    exit(EXIT_ERR);

  player->color = color;
  player->next = Human_next;
  player->Player_delete = Human_delete;
  player->obj = human;

  return player;
}