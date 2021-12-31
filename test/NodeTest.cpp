#include "gtest/gtest.h"

extern "C" {
#include "node.h"
}

class NodeTest : public ::testing::Test {
protected:
  void SetUp() override {
    board = Board_new();
    node = Node_new(board, WHITE, 10);
  }
  void TearDown() override {
    Node_delete(node);
  }
  Board *board;
  Node *node;
};

TEST_F(NodeTest, Constructor) {
  ASSERT_NE(nullptr, node);
  ASSERT_EQ(board, node->board);
  ASSERT_EQ(WHITE, node->next_color);
  ASSERT_EQ(10, node->depth);
  for (auto & child : node->children)
    ASSERT_EQ(nullptr, child);
}