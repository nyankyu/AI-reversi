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
  Board board;
  Board_make_box(&board, ""
                        "........"
                        "........"
                        "...XXX.."
                        "...XOX.."
                        "...XXX.."
                        "........"
                        "........"
                        "........"
  );
  Node *node;
  node = Node_new(&board, WHITE, 0, 1, 1);
  Evaluator_evaluate(node, WHITE);
  ASSERT_EQ(8, node->eval_point);

  node = Node_new(&board, WHITE, 0, 1, 1);
  Evaluator_evaluate(node, BLACK);
  ASSERT_EQ(-8, node->eval_point);

  node = Node_new(&board, BLACK, 0, 1, 1);
  Evaluator_evaluate(node, WHITE);
  ASSERT_EQ(0, node->eval_point);

  node = Node_new(&board, BLACK, 0, 1, 1);
  Evaluator_evaluate(node, BLACK);
  ASSERT_EQ(0, node->eval_point);
}

TEST_F(EvaluatorTest, ImportantPoint) {
  Board board;
  Board_make_box(&board, ""
                        "......OO"
                        "......OO"
                        "........"
                        "........"
                        "........"
                        "..OX...."
                        "........"
                        "........"
  );
  Node *node;
  node = Node_new(&board, WHITE, 0, 1, 1);
  Evaluator_evaluate(node, WHITE);
  ASSERT_EQ(CORNER_POINT + 1, node->eval_point);

  node = Node_new(&board, WHITE, 0, 1, 1);
  Evaluator_evaluate(node, BLACK);
  ASSERT_EQ(-(CORNER_POINT + 1), node->eval_point);

  node = Node_new(&board, BLACK, 0, 1, 1);
  Evaluator_evaluate(node, BLACK);
  ASSERT_EQ(-CORNER_POINT + 1, node->eval_point);

  node = Node_new(&board, BLACK, 0, 1, 1);
  Evaluator_evaluate(node, WHITE);
  ASSERT_EQ(-(-CORNER_POINT + 1), node->eval_point);
}

TEST_F(EvaluatorTest, ImportantPointNonCorner) {
  Board board;
  Board_make_box(&board, ""
                        "......O."
                        "......OO"
                        "........"
                        "........"
                        "........"
                        "..OX...."
                        "........"
                        "........"
                        );
  Node *node;
  node = Node_new(&board, WHITE, 0, 1, 1);
  Evaluator_evaluate(node, WHITE);
  ASSERT_EQ(-X_POINT -C_POINT -C_POINT + 1, node->eval_point);

  node = Node_new(&board, WHITE, 0, 1, 1);
  Evaluator_evaluate(node, BLACK);
  ASSERT_EQ(-(-X_POINT -C_POINT -C_POINT + 1), node->eval_point);

  node = Node_new(&board, BLACK, 0, 1, 1);
  Evaluator_evaluate(node, BLACK);
  ASSERT_EQ(1, node->eval_point);

  node = Node_new(&board, BLACK, 0, 1, 1);
  Evaluator_evaluate(node, WHITE);
  ASSERT_EQ(-1, node->eval_point);
}