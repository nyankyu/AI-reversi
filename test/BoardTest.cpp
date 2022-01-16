#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "board.h"
#include "ai-reversi.h"
}

class BoardTest : public ::testing::Test {

protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

TEST_F(BoardTest, Initialize) {
  Board board;
  Board_init(&board);
  ASSERT_EQ(BOARD_SIZE * BOARD_SIZE - 4, board.empty);
  ASSERT_EQ(2, board.white);
  ASSERT_EQ(2, board.black);

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
  ASSERT_THAT(board.box, ::testing::ContainerEq(box));
}

TEST_F(BoardTest, MakeBoxError) {
  Board board;

  ASSERT_EXIT(
      Board_make_box(&board, "sort string"),
      ::testing::ExitedWithCode(EXIT_FAILURE),
      ".*");

  ASSERT_EXIT(
      Board_make_box(&board,
                      "ABCDEFGH"
                      "illegal "
                      "char    "
                      "4       "
                      "5       "
                      "6       "
                      "7       "
                      "8       "),
      ::testing::ExitedWithCode(EXIT_FAILURE),
      ".*");
}

TEST_F(BoardTest, MakeBoxSuccess) {
  Board board;
  int W = WALL;
  int E = EMPTY;
  int box_all_empty[] = {
      W,W,W,W,W,W,W,W,W,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,E,E,E,E,E,E,E,E,
      W,W,W,W,W,W,W,W,W,W
  };
  Board_make_box(&board,
                  "........"
                  "........"
                  "........"
                  "........"
                  "........"
                  "........"
                  "........"
                  "........");
  ASSERT_THAT(box_all_empty, ::testing::ContainerEq(board.box));

  Board_make_box(&board,
                  "........"
                  "........"
                  "........"
                  "...OX..."
                  "...XO..."
                  "........"
                  "........"
                  "........");
  Board init;
  Board_init(&init);
  ASSERT_THAT(init.box, ::testing::ContainerEq(board.box));
}
