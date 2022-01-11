#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai-reversi.h"
#include "board.h"
#include "com.h"
#include "history.h"

#define BUFF_SIZE 256

static void get_input(char buff[]) {
  if (fgets(buff, BUFF_SIZE, stdin) == NULL) {
    exit(EXIT_ERR);
  }
  char *p = strchr(buff, '\n');
  if (p != NULL)
    *p = '\0';
}

static void print_prompt(int next_color) {
  printf("\n %c > ", next_color == WHITE ? 'O' : 'X');
}


int main(int argc, char **argv) {
  int ai_vs_ai = FALSE;
  if (argc == 2 && strcmp("auto", argv[1]) == 0) {
    ai_vs_ai = TRUE;
  }

  Board *board = Board_new();
  Board_init(board);
  History *history = History_new();
  History_add(history, board, BLACK);
  Com *com1;
  Com *com2;
  if (ai_vs_ai == TRUE)
    com1 = Com_new(BLACK);
  com2 = Com_new(WHITE);

  int next_color = BLACK;
  int eval_val;
  int pass_other = FALSE;

  char buff[BUFF_SIZE];
  while (1) {
    Board_print(board);
    print_prompt(next_color);
    int x;
    int y;

    if (ai_vs_ai == TRUE) {
      Com_next(com1, board, &x, &y, &eval_val);
      if (x == 0) {
        printf("PASS\n");
        if (pass_other == TRUE)
          break;
        pass_other = TRUE;
      } else {
        printf("%c%c\n", 'a' + x - 1, '1' + y - 1);
        Rule_set(board, x, y, next_color);
        pass_other = FALSE;
      }
    } else {
      if (Rule_can_pass(board, next_color) == OK) {
        pass_other = TRUE;
      } else {
        get_input(buff);
        if (strcmp(buff, "q") == 0)
          break;
        if (strcmp(buff, "r") == 0) {
          History_undo(history);
          Board_rewrite(board, history->board_array[history->current]);
          continue;
        }
        if (Rule_set_by_str(board, buff, next_color) == 0)
          continue;
        History_add(history, board, next_color);
        pass_other = FALSE;
      }
    }
    next_color = Rule_other_color(next_color);

    Board_print(board);
    print_prompt(next_color);
    Com_next(com2, board, &x, &y, &eval_val);
    if (x == 0) {
      printf("PASS\n");
      if (pass_other == TRUE)
        break;
      pass_other = TRUE;
    } else {
      printf("%c%c\n", 'a' + x - 1, '1' + y - 1);
      Rule_set(board, x, y, next_color);
      pass_other = FALSE;
    }
    next_color = Rule_other_color(next_color);
  }

  Board_delete(board);
  History_delete(history);
  if (ai_vs_ai == TRUE)
    Com_delete(com1);
  Com_delete(com2);

  //system("leaks ai-reversi");
  return EXIT_OK;
}


