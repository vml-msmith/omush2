#include "gtest/gtest.h"

class MyTest : public ::testing::Test {
protected:
  MyTest() {
  };
  ~MyTest() {
  };
};


TEST_F(MyTest, ByDefaultBazTrueIsTrue) {
  EXPECT_EQ(true, true);
}
