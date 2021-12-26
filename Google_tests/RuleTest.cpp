#include "gtest/gtest.h"
#include "gmock//gmock.h"

extern "C" {
#include "rule.h"
}

class RuleTest : public ::testing::Test {
protected:
  void SetUp() override {
    Rule_new();
  }
  void TearDown() override {
    Rule_delete();
  }
};

TEST_F(RuleTest, Constructor) {
  EXPECT_NE(nullptr, g_rule);
}

TEST_F(RuleTest, OtherColor) {
  ASSERT_EQ(WHITE, g_rule->other_color(BLACK));
  ASSERT_EQ(BLACK, g_rule->other_color(WHITE));
}

TEST_F(RuleTest, SetXYSimple) {
  int W = WALL;
  int E = EMPTY;
  int O = WHITE;
  int X = BLACK;
  int box43[] = {
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

  int box34[] = {
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

  int box65[] = {
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

  int box56[] = {
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

  int box0[] = {
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

  Board *board = Board_new();
  for (int y = 1; y <= BOARD_SIZE; y++) {
    for (int x = 1; x <= BOARD_SIZE; x++) {
      Board_init(board);
      if (x == 4 && y == 3) {
        ASSERT_EQ(2, g_rule->set(board, x, y, BLACK));
        ASSERT_THAT(box43, testing::ContainerEq(board->box));
      }
      else if (x == 3 && y == 4) {
        ASSERT_EQ(2, g_rule->set(board, x, y, BLACK));
        ASSERT_THAT(box34, testing::ContainerEq(board->box));
      }
      else if (x == 6 && y == 5) {
        ASSERT_EQ(2, g_rule->set(board, x, y, BLACK));
        ASSERT_THAT(box65, testing::ContainerEq(board->box));
      }
      else if (x == 5 && y == 6) {
        ASSERT_EQ(2, g_rule->set(board, x, y, BLACK));
        ASSERT_THAT(box56, testing::ContainerEq(board->box));
      }
      else {
        ASSERT_EQ(0, g_rule->set(board, x, y, BLACK));
        ASSERT_THAT(box0, testing::ContainerEq(board->box));
      }
    }
  }
}