#include "gtest/gtest.h"
#include "omush/framework/game.h"

using namespace omush;

class GameTest : public testing::Test {
 protected:
  //  virtual void SetUp() {}
  Game game_;
};


TEST_F(GameTest, DefaultConstructor) {
  EXPECT_EQ(game_.isInitialized(), false);
}

TEST_F(GameTest, InitializeWillSetIsInitializedToTrue) {
  EXPECT_EQ(game_.initialize(), true);
  EXPECT_EQ(game_.isInitialized(), true);
}
