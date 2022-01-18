#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "com.h"
#include "ai-reversi.h"
#include "tree.h"
#include "player.h"

inline int Com_next(Player *player, Board *board) {
  Tree *tree = Tree_new((Com *)player->obj, board, 5);

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

Com *Com_new(int color) { // TODO no static inline because called from TreeTest
  Com *com = malloc(sizeof(Com));
  if (com == NULL) {
    printf("ERROR: files malloc() Com\n");
    exit(EXIT_FAILURE);
  }
  com->color = color;

  return com;
}

inline void Com_delete(Player *player) {
  free(player->obj);
  free(player);
  Node_deletePool();
}

inline Player *Com_make_player(int color) {
  Com *com = Com_new(color);
  Player *player = malloc(sizeof(Player));
  if (player == NULL)
    exit(EXIT_FAILURE);

  player->color = color;
  player->name = "Com";
  player->next = Com_next;
  player->Player_delete = Com_delete;
  player->obj = com;
  return player;
}