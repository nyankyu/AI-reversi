#include "gtest/gtest.h"

extern "C" {
#include "com.h"
}

class ComTest : public ::testing::Test {
protected:
  Player *black;
  Player *white;
  Board board;

  void SetUp() {
    black = Com_make_player(BLACK);
    white = Com_make_player(WHITE);
  }
  void TearDown() {
    free(black);
    free(white);
  }
};

TEST_F(ComTest, MakeCom) {
  EXPECT_TRUE(white != NULL);
  ASSERT_EQ(WHITE, white->color);
  ASSERT_STREQ("Com", white->name);
  ASSERT_TRUE(white->put_next != NULL);
}

TEST_F(ComTest, DonotSetX) {
  Board_make_box(&board,
                 "........"
                 "..XO...."
                 "........"
                 "...OX..."
                 "...XO..."
                 "........"
                 "........"
                 "........");
  white->put_next(white, &board);
  ASSERT_NE(WHITE, board.box[B2]);
}

TEST_F(ComTest, DonotSetC) {
  Board_make_box(&board,
                 "..XO...."
                 "........"
                 "........"
                 "...OX..."
                 "...XO..."
                 "........"
                 "........"
                 "........");
  white->put_next(white, &board);
  ASSERT_NE(WHITE, board.box[B1]);
}

TEST_F(ComTest, SetCorner) {
  Board_make_box(&board,
                 ".XO....."
                 "........"
                 "........"
                 "...OX..."
                 "...XO..."
                 "........"
                 "........"
                 "........");
  white->put_next(white, &board);
  ASSERT_EQ(WHITE, board.box[A1]);
}

TEST_F(ComTest, EvaluateOfGameover) {
  Board_make_box(&board,
                 "........"
                 "........"
                 "..XOOO.."
                 "........"
                 "........"
                 "..XO...."
                 "........"
                 "........");
  white->put_next(white, &board);
  ASSERT_EQ(WHITE, board.box[B3]);
}