#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai-reversi.h"
#include "board.h"
#include "com.h"
#include "rule.h"

#define BUFF_SIZE 256

static void turn_color(int *color) {
  *color = *color == WHITE ? BLACK : WHITE;
}

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
    print_prompt(next_color);

    if (rule->can_pass(board, next_color) == OK) {
      pass_other = 1;
    } else {
      get_input(buff);
      if (strcmp(buff, "q") == 0)
        exit(EXIT_OK);
      if (rule->set_by_str(board, buff, next_color) == 0)
        continue;
      pass_other = 0;
    }
    turn_color(&next_color);

    int next = com->next(com, board, next_color, &eval_val);
    if (next == 0) {
      if (pass_other == 1)
        exit(EXIT_OK);
      pass_other = 1;
    } else {
      rule->set_by_index(board, next, next_color);
      pass_other = 0;
    }
    turn_color(&next_color);
  }

  Board_delete(board);

  return EXIT_OK;
}


