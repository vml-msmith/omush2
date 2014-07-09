/**
 * \file test_game.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "gtest/gtest.h"
#include "omush/framework/gameinstance.h"
#include "omush/framework/game.h"

using omush::Game;
using omush::GameInstance;

class GameTest : public testing::Test {
 protected:
  Game game_;
};


TEST_F(GameTest, DefaultConstructor) {
  EXPECT_EQ(game_.isInitialized(), false);
}

TEST_F(GameTest, InitializeWillSetIsInitializedToTrue) {
  GameInstance instance;
  EXPECT_EQ(game_.isInitialized(), false);
  EXPECT_EQ(game_.initialize(&instance), true);
  EXPECT_EQ(game_.isInitialized(), true);
}

TEST_F(GameTest, InitializeWillSetGameInstanceGameToSelf) {
  GameInstance instance;

  ASSERT_TRUE(instance.game == nullptr);
  game_.initialize(&instance);
  ASSERT_TRUE(instance.game == &game_);
}

TEST_F(GameTest, LoopShouldReturnTrueOnlyAfterBeingInitalized) {
  GameInstance instance;

  ASSERT_TRUE(game_.loop() == false);
  game_.initialize(&instance);
  ASSERT_TRUE(game_.loop() == true);
}
