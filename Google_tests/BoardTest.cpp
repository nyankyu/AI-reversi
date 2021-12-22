#include "gtest/gtest.h"

extern "C" {
#include "board.h"
}

class BoardTest : public ::testing::Test {

protected:
  virtual void SetUp() {
    board = Board_new();
  }

  virtual void TearDown() {
    Board_delete(board);
  }

  Board *board;
};

TEST_F(BoardTest, Constructor) {
  ASSERT_TRUE(board != nullptr);
}