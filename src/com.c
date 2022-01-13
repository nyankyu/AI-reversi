#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "com.h"
#include "ai-reversi.h"
#include "tree.h"
#include "player.h"

int Com_next(Player *player, Board *board) {
  Board *copy = Board_copy(board);
  Tree *tree = Tree_new((Com *)player->obj, copy, 4);

  int x = tree->root->next_x;
  int y = tree->root->next_y;
  Tree_delete(tree);

  if (x == 0) {
    if (g_print) printf("PASS\n");
    return PLAYER_PASS;
  }

  Rule_set(board, x, y, player->color);
  if (g_print) printf("%c%c\n", 'a' + x - 1, '1' + y - 1);

  return PLAYER_PUT;
}

Com *Com_new(int color) {
  Com *com = malloc(sizeof(Com));
  if (com == NULL) {
    printf("ERROR: files malloc() Com\n");
    exit(EXIT_ERR);
  }
  com->color = color;

  return com;
}

void Com_delete(Player *player) {
  free(player->obj);
  free(player);
}

Player *Com_make_player(int color) {
  Com *com = Com_new(color);
  Player *player = malloc(sizeof(Player));
  if (player == NULL)
    exit(EXIT_ERR);

  player->color = color;
  player->name = "Com";
  player->next = Com_next;
  player->Player_delete = Com_delete;
  player->obj = com;
  return player;
}