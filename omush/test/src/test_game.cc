#include "gtest/gtest.h"
#include "omush/framework/gameinstance.h"
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
  GameInstance instance;

  ASSERT_TRUE(instance.game == nullptr);
  EXPECT_EQ(game_.initialize(&instance), true);
  ASSERT_TRUE(instance.game == &game_);

  EXPECT_EQ(game_.isInitialized(), true);
}
