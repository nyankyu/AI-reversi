#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "board.h"
#include "com.h"
#include "ai-reversi.h"
#include "player.h"
#include "evaluator.h"

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  Board board;
  int next_color;
  int depth;
  int eval_value;
  Position position;
  int passed;
} BoardData;

static int best_next(BoardData *parent_data) {
  if (parent_data->depth == DEPTH_MAX) {
    Evaluator_evaluate(&parent_data->board, parent_data->next_color, &parent_data->eval_value);
    return OK;
  }

  BoardData data;
  data.board = parent_data->board;
  data.depth = parent_data->depth + 1;
  data.next_color = Rule_other_color(parent_data->next_color);
  data.passed = TRUE;

  parent_data->eval_value = INT_MAX;

  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (Rule_set(&data.board, x, y, parent_data->next_color) == 0)
        continue;
      data.passed = FALSE;
      best_next(&data);
      data.board = parent_data->board;
      // save mini evaluator point
      if (data.eval_value <= parent_data->eval_value) {
        parent_data->eval_value = data.eval_value;
        parent_data->position.x = x;
        parent_data->position.y = y;
      }
    }
  }

  if (!data.passed) {
    parent_data->eval_value *= -1;
    return OK;
  }

  // the following is the case of pass

  // The first move is a pass, the search stops.
  if (parent_data->depth == 0) {
    return COM_PASS;
  }

  // If previous move is also a pass, it's game over
  if (parent_data->passed == TRUE) {
    if (data.board.white > data.board.black) {
      if (parent_data->next_color == WHITE)
        parent_data->eval_value = INT_MAX;
      else
        parent_data->eval_value = -INT_MAX;
    } else if (data.board.white < data.board.black) {
      if (parent_data->next_color == BLACK)
        parent_data->eval_value = INT_MAX;
      else
        parent_data->eval_value = -INT_MAX;
    } else {
      parent_data->eval_value = 0;
    }
    // if the game is over, stop the search
    return COM_PASS;
  }

  best_next(&data);
  parent_data->eval_value = -data.eval_value;
  return COM_PASS;
}

int Com_next(Player *player, Board *board) {
  BoardData data;
  data.board = *board;
  data.depth = 0;
  data.next_color = player->color;
  data.passed = FALSE;

  int ret = best_next(&data);
  if (ret == COM_PASS) {
    if (g_print) printf("PASS\n");
    return PLAYER_PASS;
  }

  Rule_set(board, data.position.x, data.position.y, player->color);
  if (g_print) printf("%c%c\n", 'a' + data.position.x - 1, '1' + data.position.y - 1);

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