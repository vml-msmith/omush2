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
#include "omush/network/iserver.h"

using omush::Game;
using omush::GameInstance;
using omush::GameBuilder;
using omush::NetworkPacketDescriptorPair;
using omush::DescriptorID;
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
  MOCK_CONST_METHOD1(setupNetwork, bool(omush::IGameInstance* instance));
};

class MockNetworkManager : public omush::INetworkManager {
 public:
  MockNetworkManager() {}
  MOCK_METHOD1(addServer, bool(omush::IServer* server));
  MOCK_CONST_METHOD0(poll, void());

  MOCK_CONST_METHOD0(flush, void());
  MOCK_METHOD0(start, bool());
  MOCK_METHOD0(shutdown, bool());
  MOCK_CONST_METHOD1(sendMessage, bool(NetworkPacketDescriptorPair message));
  MOCK_CONST_METHOD1(closeConnection, bool(DescriptorID id));
  MOCK_CONST_METHOD1(getNextMessage,
                     bool(NetworkPacketDescriptorPair* message));
};

class SimpleMockGameInstance : public omush::IGameInstance {
 public:
  bool isComplete_;
  SimpleMockGameInstance() : isComplete_(false) {}
  virtual bool isComplete() const override {
    return isComplete_;
  }
};

class MockGameInstance : public SimpleMockGameInstance {
 public:
  MOCK_CONST_METHOD0(isComplete, bool());
};


TEST_F(GameTest, DefaultConstructor) {
  EXPECT_EQ(game_.isInitialized(), false);
}

TEST_F(GameTest, InitializeWillSetIsInitializedToTrue) {
  MockCompleteInstance instance;
  std::shared_ptr<omush::INetworkManager> ptr(new MockNetworkManager);
  instance.network = ptr;

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

  EXPECT_CALL(builder, setupNetwork(::testing::_)).Times(1);

  game_.initialize(&instance, &builder);
  ASSERT_TRUE(instance.game == &game_);
}

TEST_F(GameTest, InitalizeWillNotReturnTrueUnlessInstanceHasNoNulls) {
  using ::testing::NiceMock;
  // TODO(msmith): I may want to change this to test if the isComplete method is
  //               actually called rather than if things are null or not. Then
  //               the isComplete method can be tested in testing for the
  //               GameInstance class.
  MockGameInstance instance;
  NiceMock<MockBuilder> builder;

  EXPECT_CALL(instance, isComplete()).Times(1);
  EXPECT_TRUE(game_.initialize(&instance, &builder) == false);

  SimpleMockGameInstance simpleInstance;
  simpleInstance.isComplete_ = true;

  EXPECT_TRUE(game_.initialize(&simpleInstance, &builder) == true);
}

TEST_F(GameTest, LoopShouldReturnTrueOnlyAfterBeingInitalized) {
  using ::testing::NiceMock;

  NiceMock<MockBuilder> builder;
  NiceMock<MockCompleteInstance> instance;
  std::shared_ptr<omush::INetworkManager> ptr(new NiceMock<MockNetworkManager>);

  instance.network = ptr;

  ASSERT_TRUE(game_.loop() == false);

  // Suppress GMock unintersting warnings.
  EXPECT_CALL(builder, setupNetwork(::testing::_)).Times(1);
  ASSERT_TRUE(game_.initialize(&instance, &builder));

  ASSERT_TRUE(game_.loop());
}
