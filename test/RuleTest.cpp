#include "gtest/gtest.h"
#include "gmock//gmock.h"

extern "C" {
#include "rule.h"
#include "ai-reversi.h"
}

class RuleTest : public ::testing::Test {
protected:
  void SetUp() override {
    Rule_new();
  }
  void TearDown() override {
    Rule_delete();
  }
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

TEST_F(RuleTest, Constructor) {
  EXPECT_NE(nullptr, g_rule);
}

TEST_F(RuleTest, OtherColor) {
  ASSERT_EQ(WHITE, g_rule->other_color(BLACK));
  ASSERT_EQ(BLACK, g_rule->other_color(WHITE));
}

::testing::AssertionResult BoxEQ(int expected[], int actual[]) {
  for (int i = 0; i < BOX_SIZE; i++) {
    if (expected[i] != actual[i]) {
      return ::testing::AssertionFailure() << "failure index : " << i;
    }
  }
  return ::testing::AssertionSuccess();
}

TEST_F(RuleTest, SetXYSimple) {
  Board *board = Board_new();
  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      Board_init(board);
      if (x == 4 && y == 3) {
        ASSERT_EQ(2, g_rule->set(board, x, y, BLACK));
        ASSERT_TRUE(BoxEQ(box43, board->box));
      }
      else if (x == 3 && y == 4) {
        ASSERT_EQ(2, g_rule->set(board, x, y, BLACK));
        ASSERT_TRUE(BoxEQ(box34, board->box));
      }
      else if (x == 6 && y == 5) {
        ASSERT_EQ(2, g_rule->set(board, x, y, BLACK));
        ASSERT_TRUE(BoxEQ(box65, board->box));
      }
      else if (x == 5 && y == 6) {
        ASSERT_EQ(2, g_rule->set(board, x, y, BLACK));
        ASSERT_TRUE(BoxEQ(box56, board->box));
      }
      else {
        ASSERT_EQ(0, g_rule->set(board, x, y, BLACK));
        ASSERT_TRUE(BoxEQ(box0, board->box));
      }
    }
  }
}

TEST_F(RuleTest, SetByStrSimple) {
  Board *board = Board_new();
  char str[] = "..";
  for (str[0] = 'A'; str[0] <= 'H'; str[0]++) {
    for (str[1] = '1'; str[1] <= '8'; str[1]++) {
      Board_init(board);
      if (strcmp("D3", str) == 0) {
        ASSERT_EQ(2, g_rule->set_by_str(board, str, BLACK));
        ASSERT_TRUE(BoxEQ(box43, board->box));
      }
      else if (strcmp("C4", str) == 0) {
        ASSERT_EQ(2, g_rule->set_by_str(board, str, BLACK));
        ASSERT_TRUE(BoxEQ(box34, board->box));
      }
      else if (strcmp("F5", str) == 0) {
        ASSERT_EQ(2, g_rule->set_by_str(board, str, BLACK));
        ASSERT_TRUE(BoxEQ(box65, board->box));
      }
      else if (strcmp("E6", str) == 0) {
        ASSERT_EQ(2, g_rule->set_by_str(board, str, BLACK));
        ASSERT_TRUE(BoxEQ(box56, board->box));
      }
      else {
        ASSERT_EQ(0, g_rule->set_by_str(board, str, BLACK));
        ASSERT_TRUE(BoxEQ(box0, board->box));
      }
    }
  }
}

TEST_F(RuleTest, SetByIndexSimple) {
  Board *board = Board_new();
  for (int i = 0; i < BOX_SIZE; i++) {
      Board_init(board);
      if (i == 31) {
        ASSERT_EQ(2, g_rule->set_by_index(board, i, BLACK));
        ASSERT_TRUE(BoxEQ(box43, board->box));
      }
      else if (i == 39) {
        ASSERT_EQ(2, g_rule->set_by_index(board, i, BLACK));
        ASSERT_TRUE(BoxEQ(box34, board->box));
      }
      else if (i == 51) {
        ASSERT_EQ(2, g_rule->set_by_index(board, i, BLACK));
        ASSERT_TRUE(BoxEQ(box65, board->box));
      }
      else if (i == 59) {
        ASSERT_EQ(2, g_rule->set_by_index(board, i, BLACK));
        ASSERT_TRUE(BoxEQ(box56, board->box));
      }
      else {
        ASSERT_EQ(0, g_rule->set_by_index(board, i, BLACK));
        ASSERT_TRUE(BoxEQ(box0, board->box));
      }
  }
}

TEST_F(RuleTest, CanSetSimple) {
  Board *board = Board_new();
  Board_init(board);
  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      if (x == 4 && y == 3) {
        ASSERT_EQ(OK, g_rule->can_set(board, x, y, BLACK));
      }
      else if (x == 3 && y == 4) {
        ASSERT_EQ(OK, g_rule->can_set(board, x, y, BLACK));
      }
      else if (x == 6 && y == 5) {
        ASSERT_EQ(OK, g_rule->can_set(board, x, y, BLACK));
      }
      else if (x == 5 && y == 6) {
        ASSERT_EQ(OK, g_rule->can_set(board, x, y, BLACK));
      }
      else {
        ASSERT_EQ(NG, g_rule->can_set(board, x, y, BLACK));
      }
    }
  }
}

TEST_F(RuleTest, CanPass) {
  Board *board = Board_new();

  Board_init(board);
  board->box[40] = X;
  board->box[50] = X;
  ASSERT_EQ(OK, g_rule->can_pass(board, BLACK));

  int box_full[BOX_SIZE] = {
      W,W,W,W,W,W,W,W,W,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,W,W,W,W,W,W,W,W,W
  };
  memcpy(board->box, box_full, sizeof(int) * BOX_SIZE);
  ASSERT_EQ(OK, g_rule->can_pass(board, BLACK));

  int box_empty[BOX_SIZE] = {
      W,W,W,W,W,W,W,W,W,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,O,O,O,O,O,O,O,O,
      W,W,W,W,W,W,W,W,W,W
  };
  memcpy(board->box, box_empty, sizeof(int) * BOX_SIZE);
  ASSERT_EQ(OK, g_rule->can_pass(board, BLACK));

  int box_all_dir[BOX_SIZE] = {
      W,W,W,W,W,W,W,W,W,
      W,O,X,X,O,X,X,O,X,
      W,X,O,O,O,O,O,O,X,
      W,X,O,O,O,O,O,O,X,
      W,O,O,O,E,O,O,O,O,
      W,X,O,O,O,O,O,O,X,
      W,X,O,O,O,O,O,O,X,
      W,O,O,O,O,O,O,O,X,
      W,X,X,X,O,X,X,X,O,
      W,W,W,W,W,W,W,W,W,W
  };
  memcpy(board->box, box_all_dir, sizeof(int) * BOX_SIZE);
  ASSERT_EQ(OK, g_rule->can_pass(board, BLACK));
}