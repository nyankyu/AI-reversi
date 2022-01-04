#include "gtest/gtest.h"
#include "board.h"

::testing::AssertionResult BoxEQ(const int expected[], const int actual[]) {
  for (int i = 0; i < BOX_SIZE; i++) {
    if (expected[i] != actual[i]) {
      return ::testing::AssertionFailure() << "failure index : " << i;
    }
  }
  return ::testing::AssertionSuccess();
}
