#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "board.h"
#include "com.h"
#include "ai-reversi.h"
#include "player.h"
#include "evaluator.h"

static int best_next(Board *board, int next_color, Point *point, int *eval_point, int depth) {
  if (depth == DEPTH_MAX) {
    Evaluator_evaluate(board, next_color, eval_point);
    return OK;
  }

  Point temp_point = {0, 0};
  int temp_eval_point;
  Board temp_board;
  int other_color = Rule_other_color(next_color);
  int pass = TRUE;

  *eval_point = INT_MAX;
  temp_board = *board;

  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (Rule_set(&temp_board, x, y, next_color) == 0)
        continue;
      pass = FALSE;
      temp_point.x = x;
      temp_point.y = y;
      best_next(&temp_board, other_color, &temp_point, &temp_eval_point, depth + 1);
      temp_board = *board;
      // save mini evaluator point
      if (temp_eval_point <= *eval_point) {
        *eval_point = temp_eval_point;
        point->x = x;
        point->y = y;
      }
    }
  }

  if (!pass) {
    *eval_point *= -1;
    return OK;
  }

  // the following is the case of pass

  // The first move is a pass, the search stops.
  if (depth == 0) {
    return COM_PASS;
  }

  // If previous move is also a pass, it's game over
  if (temp_point.x == 0) {
    if (board->white > board->black) {
      if (next_color == WHITE)
        *eval_point = INT_MAX;
      else
        *eval_point = -INT_MAX;
    } else if (board->white < board->black) {
      if (next_color == BLACK)
        *eval_point = INT_MAX;
      else
        *eval_point = -INT_MAX;
    }
    return COM_PASS;
  }

  best_next(board, other_color, &temp_point, eval_point, depth + 1);
  return COM_PASS;
}

int Com_next(Player *player, Board *board) {
  Board temp_board = *board;
  Point point;
  int eval_point;

  int ret = best_next(&temp_board, player->color, &point, &eval_point, 0);
  if (ret == COM_PASS) {
    if (g_print) printf("PASS\n");
    return PLAYER_PASS;
  }

  Rule_set(board, point.x, point.y, player->color);
  if (g_print) printf("%c%c\n", 'a' + point.x - 1, '1' + point.y - 1);

  return PLAYER_PUT;
}

Player *Com_make_player(int color) {
  Player *player = malloc(sizeof(Player));
  if (player == NULL)
    exit(EXIT_FAILURE);

  player->color = color;
  player->name = "Com";
  player->put_next = Com_next;
  return player;
}