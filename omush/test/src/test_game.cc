/**
 * \file test_game.cc
 *
 * Copyright 2014 Michael Smith
 */
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "omush/framework/gameinstance.h"
#include "omush/framework/game.h"
#include "omush/framework/gamebuilder.h"

using omush::Game;
using omush::GameInstance;
using omush::GameBuilder;

class GameTest : public testing::Test {
 protected:
  Game game_;
};

class MockBuilder : public GameBuilder {
 public:
  MockBuilder() {
    setupNetwork_ = false;
  }

  bool setupNetwork() {
    setupNetwork_ = true;
  }

  bool setupNetwork_;
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

TEST_F(GameTest, InitializeWithBuilderWillRunBuilderSetupSteps) {
  GameInstance instance;
  MockBuilder builder;

  ASSERT_TRUE(builder.setupNetwork_ == false);
  game_.initialize(&instance, &builder);
  ASSERT_TRUE(builder.setupNetwork_ == true);
}

TEST_F(GameTest, LoopShouldReturnTrueOnlyAfterBeingInitalized) {
  GameInstance instance;

  ASSERT_TRUE(game_.loop() == false);
  game_.initialize(&instance);
  ASSERT_TRUE(game_.loop() == true);
}
