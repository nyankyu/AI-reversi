#include <stdio.h>
#include <stdlib.h>
#include "measure.h"
#include "player.h"
#include "com.h"
#include "com_rand.h"

#define GAME_SIZE 50

void Measure_start(void) {
  g_print = 0;
  Player *white = Com_make_player(WHITE);
  Player *black = Com_rand_make_player(BLACK);
  Player *player = black;
  Board board;

  printf("==== AI-reversi ====\n");

  for (int i = 0; i < 2; i++) {
    int pass = 0;
    int game_count = GAME_SIZE;
    int win_white = 0;
    int win_black = 0;

    while (game_count--) {
      fprintf(stderr, "\r%10d", game_count);
      Board_init(&board);

      while (1) {
        int result = player->put_next(player, &board);
        if (result == PLAYER_PUT) {
          pass = 0;
        } else if (result == PLAYER_PASS) {
          if (pass == 1)
            break;
          pass++;
        } else if (result == PLAYER_ERR) {
          exit(EXIT_FAILURE);
        } else if (result == PLAYER_NG) {
          continue;
        }
        player = (player == white) ? black : white;
      }

      if (board.white > board.black)
        win_white++;
      else if (board.black > board.white)
        win_black++;
    }

    printf("\rWhite[%s]: %d, Black[%s]: %d, Draw: %d\n", white->name, win_white, black->name, win_black, GAME_SIZE - win_white - win_black);

    free(white);
    free(black);
    white = Com_rand_make_player(WHITE);
    black = Com_make_player(BLACK);
    player = black;
  }
  free(white);
  free(black);

  //system("leaks ai-reversi");
}
