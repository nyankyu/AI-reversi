#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai-reversi.h"
#include "board.h"
#include "com.h"
#include "rule.h"

#define BUFF_SIZE 256

void turn_color(int *color) {
  *color = *color == WHITE ? BLACK : WHITE;
}

void get_input(char buff[]) {
  if (fgets(buff, BUFF_SIZE, stdin) == NULL) {
    exit(EXIT_ERR);
  }
  char *p = strchr(buff, '\n');
  if (p != NULL)
    *p = '\0';
}

int main(void) {
  Rule *rule = Rule_new();
  Board *board = Board_new();
  Com *com = Com_new(rule, BLACK);

  int next_color = WHITE;
  int eval_val;
  int pass_other = 0;

  char buff[BUFF_SIZE];
  while (1) {
    board->print(board);
    printf("\n %c > ", next_color == WHITE ? 'O' : 'X');

    if (rule->can_pass(board, next_color) == NG) {
      get_input(buff);
      if (strcmp(buff, "q") == 0)
        exit(EXIT_OK);
      if (rule->set_by_str(board, buff, next_color) == 0)
        continue;
      turn_color(&next_color);
      pass_other = 0;
    } else {
      pass_other = 1;
    }

    int next = com->next(com, board, next_color, &eval_val);
    if (next == 0) {
      if (pass_other == 1)
        exit(EXIT_OK);
      pass_other = 1;
      continue;
    }
    rule->set_by_index(board, next, next_color);
    turn_color(&next_color);
    pass_other = 0;
  }

  Board_delete(board);

  return EXIT_OK;
}


