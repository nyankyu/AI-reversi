#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "tree.h"
#include "rule.h"
}

class TreeTest : public ::testing::Test {
protected:
  void SetUp() override {
    Rule_new();
    board = Board_new();
    Board_init(board);
    tree = Tree_new(board, BLACK, 1);
  }
  void TearDown() override {
    Tree_delete(tree);
    Rule_delete();
  }
  Board *board;
  Tree *tree;
};

TEST_F(TreeTest, ConstructorMemberValue) {
  EXPECT_NE(nullptr, tree);
  ASSERT_EQ(BLACK, tree->my_color);
  EXPECT_NE(nullptr, tree->root);
  ASSERT_EQ(0, tree->root->depth);
  ASSERT_EQ(WHITE, tree->root->next_color);
  ASSERT_EQ(board, tree->root->board);
}

int W = WALL;
int E = EMPTY;
int O = WHITE;
int X = BLACK;
int box0[] = {
    W,W,W,W,W,W,W,W,W,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,O,E,E,E,
    W,E,E,E,O,O,E,E,E,
    W,E,E,E,X,O,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,W,W,W,W,W,W,W,W,W
};

int box1[] = {
    W,W,W,W,W,W,W,W,W,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,O,O,O,E,E,
    W,E,E,E,X,O,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,W,W,W,W,W,W,W,W,W
};

int box2[] = {
    W,W,W,W,W,W,W,W,W,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,O,X,E,E,E,
    W,E,E,O,O,O,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,W,W,W,W,W,W,W,W,W
};

int box3[] = {
    W,W,W,W,W,W,W,W,W,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,O,X,E,E,E,
    W,E,E,E,O,O,E,E,E,
    W,E,E,E,O,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,E,E,E,E,E,E,E,E,
    W,W,W,W,W,W,W,W,W,W
};
TEST_F(TreeTest, ConstractorBuildTree) {
  EXPECT_NE(nullptr, tree->root->children[0]);
  Node *child;
  child = tree->root->children[0];
  ASSERT_EQ(BLACK, child->next_color);
  ASSERT_EQ(1, child->depth);
  ASSERT_THAT(box0, testing::ContainerEq(child->board->box));
  ASSERT_EQ(nullptr, child->children[0]);
  child = tree->root->children[1];
  ASSERT_EQ(BLACK, child->next_color);
  ASSERT_EQ(1, child->depth);
  ASSERT_THAT(box1, testing::ContainerEq(child->board->box));
  ASSERT_EQ(nullptr, child->children[0]);
  child = tree->root->children[2];
  ASSERT_EQ(BLACK, child->next_color);
  ASSERT_EQ(1, child->depth);
  ASSERT_THAT(box2, testing::ContainerEq(child->board->box));
  ASSERT_EQ(nullptr, child->children[0]);
  child = tree->root->children[3];
  ASSERT_EQ(BLACK, child->next_color);
  ASSERT_EQ(1, child->depth);
  ASSERT_THAT(box3, testing::ContainerEq(child->board->box));
  ASSERT_EQ(nullptr, child->children[0]);
  ASSERT_EQ(nullptr, tree->root->children[4]);
}