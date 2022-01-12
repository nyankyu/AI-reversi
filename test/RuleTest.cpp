#include "gtest/gtest.h"

extern "C" {
#include "rule.h"
#include "ai-reversi.h"
}

extern ::testing::AssertionResult BoxEQ(const int expected[], const int actual[]);

class RuleTest : public ::testing::Test {
protected:
  void SetUp() override {
    board = Board_new();
  }
  void TearDown() override {
    Board_delete(board);
  }
  Board *board;

  int W = WALL;
  int E = EMPTY;
  int O = WHITE;
  int X = BLACK;
  int box43[BOX_SIZE] = {
      W,W,W,W,W,W,W,W,W,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,X,E,E,E,E,
      W,E,E,E,X,X,E,E,E,
      W,E,E,E,X,O,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,W,W,W,W,W,W,W,W,W
  };

  int box34[BOX_SIZE] = {
      W,W,W,W,W,W,W,W,W,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,X,X,X,E,E,E,
      W,E,E,E,X,O,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,W,W,W,W,W,W,W,W,W
  };

  int box65[BOX_SIZE] = {
      W,W,W,W,W,W,W,W,W,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,O,X,E,E,E,
      W,E,E,E,X,X,X,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,W,W,W,W,W,W,W,W,W
  };

  int box56[BOX_SIZE] = {
      W,W,W,W,W,W,W,W,W,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,O,X,E,E,E,
      W,E,E,E,X,X,E,E,E,
      W,E,E,E,E,X,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,W,W,W,W,W,W,W,W,W
  };

  int box0[BOX_SIZE] = {
      W,W,W,W,W,W,W,W,W,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,O,X,E,E,E,
      W,E,E,E,X,O,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,W,W,W,W,W,W,W,W,W
  };

};

TEST_F(RuleTest, SetXY_1stMove) {
  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      Board_init(board);
      if (x == 4 && y == 3) {
        ASSERT_EQ(2, Rule_set(board, x, y, BLACK));
        ASSERT_TRUE(BoxEQ(box43, board->box));
      }
      else if (x == 3 && y == 4) {
        ASSERT_EQ(2, Rule_set(board, x, y, BLACK));
        ASSERT_TRUE(BoxEQ(box34, board->box));
      }
      else if (x == 6 && y == 5) {
        ASSERT_EQ(2, Rule_set(board, x, y, BLACK));
        ASSERT_TRUE(BoxEQ(box65, board->box));
      }
      else if (x == 5 && y == 6) {
        ASSERT_EQ(2, Rule_set(board, x, y, BLACK));
        ASSERT_TRUE(BoxEQ(box56, board->box));
      }
      else {
        ASSERT_EQ(0, Rule_set(board, x, y, BLACK));
        ASSERT_TRUE(BoxEQ(box0, board->box));
      }
    }
  }
}

TEST_F(RuleTest, SetByStr_1stMove) {
  char str[] = "..";
  for (str[0] = 'A'; str[0] <= 'H'; str[0]++) {
    for (str[1] = '1'; str[1] <= '8'; str[1]++) {
      Board_init(board);
      if (strcmp("D3", str) == 0) {
        ASSERT_EQ(2, Rule_set_by_str(board, str, BLACK));
        ASSERT_TRUE(BoxEQ(box43, board->box));
      }
      else if (strcmp("C4", str) == 0) {
        ASSERT_EQ(2, Rule_set_by_str(board, str, BLACK));
        ASSERT_TRUE(BoxEQ(box34, board->box));
      }
      else if (strcmp("F5", str) == 0) {
        ASSERT_EQ(2, Rule_set_by_str(board, str, BLACK));
        ASSERT_TRUE(BoxEQ(box65, board->box));
      }
      else if (strcmp("E6", str) == 0) {
        ASSERT_EQ(2, Rule_set_by_str(board, str, BLACK));
        ASSERT_TRUE(BoxEQ(box56, board->box));
      }
      else {
        ASSERT_EQ(0, Rule_set_by_str(board, str, BLACK));
        ASSERT_TRUE(BoxEQ(box0, board->box));
      }
    }
  }
}

TEST_F(RuleTest, CanSet_1stMove) {
  Board_init(board);
  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (x == 4 && y == 3) {
        ASSERT_EQ(OK, Rule_can_set(board, x, y, BLACK));
      }
      else if (x == 3 && y == 4) {
        ASSERT_EQ(OK, Rule_can_set(board, x, y, BLACK));
      }
      else if (x == 6 && y == 5) {
        ASSERT_EQ(OK, Rule_can_set(board, x, y, BLACK));
      }
      else if (x == 5 && y == 6) {
        ASSERT_EQ(OK, Rule_can_set(board, x, y, BLACK));
      }
      else {
        ASSERT_EQ(NG, Rule_can_set(board, x, y, BLACK));
      }
    }
  }
}

TEST_F(RuleTest, CanPass_OK) {
  Board_init(board);
  board->box[40] = X;
  board->box[50] = X;
  ASSERT_EQ(OK, Rule_can_pass(board, BLACK));

  Board_make_box(board, ""
                  "OOOOOOOO"
                  "OOOOOOOO"
                  "OOOOOOOO"
                  "OOOOOOOO"
                  "OOOOOOOO"
                  "OOOOOOOO"
                  "OOOOOOOO"
                  "OOOOOOOO"
                  );
  ASSERT_EQ(OK, Rule_can_pass(board, BLACK));

  Board_make_box(board, ""
                  "........"
                  "........"
                  "........"
                  "........"
                  "........"
                  "........"
                  "........"
                  "........"
                  );
  ASSERT_EQ(OK, Rule_can_pass(board, BLACK));

  Board_make_box(board,
                  "O X X O X X O X"
                  "X O O O O O O X"
                  "X O O O O O O X"
                  "O O O . O O O O"
                  "X O O O O O O X"
                  "X O O O O O O X"
                  "O O O O O O O X"
                  "X X X O X X X O"
                  );
  ASSERT_EQ(OK, Rule_can_pass(board, BLACK));
}

TEST_F(RuleTest, CanPass_NG) {
  Board_init(board);

  ASSERT_EQ(NG, Rule_can_pass(board, WHITE));
  ASSERT_EQ(NG, Rule_can_pass(board, BLACK));

  Board_make_box(board,
                  "X O O X O O X O"
                  "O O O O O O O O"
                  "O O O O O O O O"
                  "X O O . O O O X"
                  "O O O O O O O O"
                  "O O O O O O O O"
                  "X O O O O O O O"
                  "O O O X O O O X"
  );
  ASSERT_EQ(NG, Rule_can_pass(board, BLACK));

  Board_make_box(board,
                  "O X X O X X O X"
                  "X X X X X X X X"
                  "X X X X X X X X"
                  "O X X . X X X O"
                  "X X X X X X X X"
                  "X X X X X X X X"
                  "O X X X X X X X"
                  "X X X O X X X O"
  );
  ASSERT_EQ(NG, Rule_can_pass(board, WHITE));

  Board_make_box(board,
                  ". . . . . . . ."
                  ". . . . . . . ."
                  ". . . . . . . ."
                  ". . X X O O . ."
                  ". . . . . . . ."
                  ". . . . . . . ."
                  ". . . . . . . ."
                  ". . . . . . . ."
  );
  ASSERT_EQ(NG, Rule_can_pass(board, BLACK));
  ASSERT_EQ(NG, Rule_can_pass(board, WHITE));

  Board_make_box(board,
                  ". . . . . . . ."
                  ". . . . X . . ."
                  ". . . . X . . ."
                  ". . . . O . . ."
                  ". . . . O . . ."
                  ". . . . . . . ."
                  ". . . . . . . ."
                  ". . . . . . . ."
  );
  ASSERT_EQ(NG, Rule_can_pass(board, BLACK));
  ASSERT_EQ(NG, Rule_can_pass(board, WHITE));

  Board_make_box(board,
                  ". . . . . . . ."
                  ". . X . . . . ."
                  ". . . X . . . ."
                  ". . . . O . . ."
                  ". . . . . O . ."
                  ". . . . . . . ."
                  ". . . . . . . ."
                  ". . . . . . . ."
                  );
  ASSERT_EQ(NG, Rule_can_pass(board, BLACK));
  ASSERT_EQ(NG, Rule_can_pass(board, WHITE));
}
