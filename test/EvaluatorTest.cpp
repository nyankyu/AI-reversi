#include "gtest/gtest.h"

extern "C" {
#include "evaluator.h"
}

::testing::AssertionResult BoxEQ(const int expected[], const int actual[]);

class EvaluatorTest : public ::testing::Test {
protected:
  void SetUp() {
  }
  void TearDown() {
  }
};

TEST_F(EvaluatorTest, AvailablePoint) {
  int eval_point;
  Board board;
  Board_make_box(&board,
                 "........"
                 "........"
                 "...XXX.."
                 "...XOX.."
                 "...XXX.."
                 "........"
                 "........"
                 "........");

  Evaluator_evaluate(&board, WHITE, &eval_point);
  ASSERT_EQ(8, eval_point);

  Evaluator_evaluate(&board, BLACK, &eval_point);
  ASSERT_EQ(0, eval_point);
}

TEST_F(EvaluatorTest, ImportantPoint) {
  int eval_point;
  Board board;
  Board_make_box(&board,
                 "......OO"
                 "......OO"
                 "........"
                 "........"
                 "........"
                 "..OX...."
                 "........"
                 "........"
                 );

  Evaluator_evaluate(&board, WHITE, &eval_point);
  ASSERT_EQ(CORNER_POINT + 1, eval_point);

  Evaluator_evaluate(&board, BLACK, &eval_point);
  ASSERT_EQ(-CORNER_POINT + 1, eval_point);
}

TEST_F(EvaluatorTest, ImportantPointNonCorner) {
  int eval_point;
  Board board;
  Board_make_box(&board,
                 "......O."
                 "......OO"
                 "........"
                 "........"
                 "........"
                 "..OX...."
                 "........"
                 "........");

  Evaluator_evaluate(&board, WHITE, &eval_point);
  ASSERT_EQ(-X_POINT -C_POINT -C_POINT + 1, eval_point);

  Evaluator_evaluate(&board, BLACK, &eval_point);
  ASSERT_EQ(X_POINT + C_POINT + C_POINT + 1, eval_point);
}
