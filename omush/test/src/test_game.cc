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
