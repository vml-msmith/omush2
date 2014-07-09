/**
 * \file test_gamebuilder.cc
 *
 * Copyright 2014 Michael Smith
 */
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "omush/framework/gamebuilder.h"
#include "omush/framework/gameinstance.h"

class GameBuilderTest : public testing::Test {
 protected:
  omush::GameBuilder builder_;
};

/*
class MockBuilder : public GameBuilder {
 public:
  MOCK_CONST_METHOD0(setupNetwork, bool());
};
*/

TEST_F(GameBuilderTest, SetupNetworkSetsUpNetwork) {
  omush::GameInstance instance;

  ASSERT_TRUE(instance.network == nullptr);
  builder_.setupNetwork(&instance);
  ASSERT_TRUE(instance.network != nullptr);
}
