#include "gtest/gtest.h"

extern "C" {
#include "evaluator.h"
#include "tree.h"
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
  Board *board = Board_new();
  Board_make_box(board, ""
                        "........"
                        "........"
                        "...XXX.."
                        "...XOX.."
                        "...XXX.."
                        "........"
                        "........"
                        "........"
  );
  Node *node = Node_new(board, WHITE, 0, 1, 1);
  Evaluator_evaluate(node);
  ASSERT_EQ(8, node->eval_point);

  node = Node_new(board, BLACK, 0, 1, 1);
  Evaluator_evaluate(node);
  ASSERT_EQ(8, node->eval_point);
}

TEST_F(EvaluatorTest, ImportantPoint) {
  Board *board = Board_new();
  Board_make_box(board, ""
                        "......OO"
                        "......OO"
                        "........"
                        "........"
                        "........"
                        "..OX...."
                        "........"
                        "........"
  );
  Node *node = Node_new(board, WHITE, 0, 1, 1);
  Evaluator_evaluate(node);
  ASSERT_EQ(80 + 1, node->eval_point);

  node = Node_new(board, BLACK, 0, 1, 1);
  Evaluator_evaluate(node);
  ASSERT_EQ(-80 + 1, node->eval_point);
}

TEST_F(EvaluatorTest, ImportantPointNonCorner) {
  Board *board = Board_new();
  Board_make_box(board, ""
                        "......O."
                        "......OO"
                        "........"
                        "........"
                        "........"
                        "..OX...."
                        "........"
                        "........"
                        );
  Node *node = Node_new(board, WHITE, 0, 1, 1);
  Evaluator_evaluate(node);
  ASSERT_EQ(- 50 - 30 - 30 + 1, node->eval_point);

  node = Node_new(board, BLACK, 0, 1, 1);
  Evaluator_evaluate(node);
  ASSERT_EQ(50 + 30 + 30 + 1, node->eval_point);
}