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

TEST_F(GameBuilderTest, SetupNetworkSetsUpNetwork) {
  omush::GameInstance instance;

  ASSERT_TRUE(instance.network == nullptr);
  builder_.setupNetwork(&instance);
  ASSERT_TRUE(instance.network != nullptr);
}

TEST_F(GameBuilderTest, SetupDatabaseSetsUpDatabase) {
  omush::GameInstance instance;
  ASSERT_TRUE(instance.database == nullptr);
  builder_.setupDatabase(&instance);
  ASSERT_TRUE(instance.database != nullptr);
}
