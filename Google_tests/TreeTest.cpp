#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "tree.h"
#include "rule.h"
#include "ai-reversi.h"
}

class TreeTest : public ::testing::Test {
protected:
  void SetUp() override {
    g_rule = Rule_new();
    board = Board_new();
    Board_init(board);
    tree = Tree_new(board, BLACK, 2);
  }
  void TearDown() override {
    Tree_delete(tree);
    Rule_delete(g_rule);
  }
  Board *board;
  Tree *tree;
};

TEST_F(TreeTest, Constructor) {
  EXPECT_NE(nullptr, tree);
  ASSERT_EQ(BLACK, tree->my_color);
  EXPECT_NE(nullptr, tree->root);
  ASSERT_EQ(0, tree->root->depth);
  ASSERT_EQ(board, tree->root->board);
}

TEST_F(TreeTest, BuildTree) {

}