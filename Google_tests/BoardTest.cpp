#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "board.h"
}

class BoardTest : public ::testing::Test {

protected:
  void SetUp() override {
    board = Board_new();
  }

  void TearDown() override {
    Board_delete(board);
  }

  Board *board;
};

TEST_F(BoardTest, Constructor) {
  ASSERT_TRUE(board != nullptr);
  ASSERT_TRUE(board->print != nullptr);
}

TEST_F(BoardTest, Initialize) {
  Board_init(board);
  ASSERT_EQ(BOARD_SIZE * BOARD_SIZE - 4, board->empty);
  ASSERT_EQ(2, board->white);
  ASSERT_EQ(2, board->black);

  int W = WALL;
  int E = EMPTY;
  int O = WHITE;
  int X = BLACK;
  int box[] = {
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
  ASSERT_THAT(board->box, ::testing::ContainerEq(box));
}

TEST_F(BoardTest, Copy) {
  board->box[0] = 10;
  board->box[BOARD_SIZE + 1] = 11;
  board->box[10] = 12;
  board->box[20] = 13;
  board->box[BOX_SIZE - 1] = 14;
  Board *copy = Board_copy(board);
  ASSERT_THAT(board->box, ::testing::ContainerEq(copy->box));
}