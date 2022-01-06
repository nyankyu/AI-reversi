#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai-reversi.h"
#include "board.h"
#include "com.h"

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

  Rule_new();
  Board *board = Board_new();
  Board_init(board);
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
    board->print(board);
    print_prompt(next_color);
    int x;
    int y;

    if (ai_vs_ai == TRUE) {
      com1->next(com1, board, &x, &y, &eval_val);
      if (x == 0) {
        printf("PASS\n");
        if (pass_other == TRUE)
          break;
        pass_other = TRUE;
      } else {
        printf("%c%c\n", 'a' + x - 1, '1' + y - 1);
        g_rule->set(board, x, y, next_color);
        pass_other = FALSE;
      }
    } else {
      if (g_rule->can_pass(board, next_color) == OK) {
        pass_other = TRUE;
      } else {
        get_input(buff);
        if (strcmp(buff, "q") == 0)
          break;
        if (g_rule->set_by_str(board, buff, next_color) == 0)
          continue;
        pass_other = FALSE;
      }
    }
    next_color = g_rule->other_color(next_color);

    board->print(board);
    print_prompt(next_color);
    com2->next(com2, board, &x, &y, &eval_val);
    if (x == 0) {
      printf("PASS\n");
      if (pass_other == TRUE)
        break;
      pass_other = TRUE;
    } else {
      printf("%c%c\n", 'a' + x - 1, '1' + y - 1);
      g_rule->set(board, x, y, next_color);
      pass_other = FALSE;
    }
    next_color = g_rule->other_color(next_color);
  }

  Rule_delete();
  Board_delete(board);
  if (ai_vs_ai == TRUE)
    Com_delete(com1);
  Com_delete(com2);

  //system("leaks ai-reversi");
  return EXIT_OK;
}


