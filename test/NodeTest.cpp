#include "gtest/gtest.h"

extern "C" {
#include "node.h"
}

class NodeTest : public ::testing::Test {
protected:
  void SetUp() override {
    Board board;
    Board_init(&board);
    node = Node_new(&board, WHITE, 10, 1, 1);
  }
  void TearDown() override {
  }
  Node *node;
};

TEST_F(NodeTest, Constructor) {
  ASSERT_NE(nullptr, node);
  ASSERT_EQ(WHITE, node->next_color);
  ASSERT_EQ(10, node->depth);
  ASSERT_EQ(1, node->last_x);
  ASSERT_EQ(1, node->last_y);
  for (auto & child : node->children)
    ASSERT_EQ(nullptr, child);
}