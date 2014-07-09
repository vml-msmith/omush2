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
#include "omush/network/inetworkmanager.h"

using omush::Game;
using omush::GameInstance;
using omush::GameBuilder;
using ::testing::AtLeast;

class GameTest : public testing::Test {
 protected:
  Game game_;
};

class MockCompleteInstance : public GameInstance {
 public:
  virtual bool isComplete() const override {
    return true;
  }
};

class MockBuilder : public GameBuilder {
 public:
  MOCK_CONST_METHOD0(setupNetwork, bool());
};

class MockNetworkManager : public omush::INetworkManager {
 public:
  MockNetworkManager() {}
};

TEST_F(GameTest, DefaultConstructor) {
  EXPECT_EQ(game_.isInitialized(), false);
}

TEST_F(GameTest, InitializeWillSetIsInitializedToTrue) {
  MockCompleteInstance instance;

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

  EXPECT_CALL(builder, setupNetwork()).Times(1);

  game_.initialize(&instance, &builder);
  ASSERT_TRUE(instance.game == &game_);
}

TEST_F(GameTest, InitalizeWillNotReturnTrueUnlessInstanceHasNoNulls) {
  // TODO(msmith): I may want to change this to test if the isComplete method is
  //               actually called rather than if things are null or not. Then
  //               the isComplete method can be tested in testing for the
  //               GameInstance class.
  GameInstance instance;
  MockBuilder builder;

  EXPECT_TRUE(instance.network == nullptr);
  EXPECT_TRUE(game_.initialize(&instance, &builder) == false);
  EXPECT_EQ(game_.isInitialized(), false);

  std::shared_ptr<omush::INetworkManager> ptr(new MockNetworkManager);
  instance.network = ptr;

  EXPECT_TRUE(game_.initialize(&instance, &builder) == true);
  EXPECT_EQ(game_.isInitialized(), true);
}

TEST_F(GameTest, LoopShouldReturnTrueOnlyAfterBeingInitalized) {
  MockCompleteInstance instance;

  ASSERT_TRUE(game_.loop() == false);
  game_.initialize(&instance);

  ASSERT_TRUE(game_.loop() == true);
}
