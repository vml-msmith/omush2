/**
 * \file test_networkmanager.cc
 *
 * Copyright 2014 Michael Smith
 */
#include <stdio.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "omush/network/networkmanager.h"
#include "omush/network/iserver.h"

using omush::IServer;

class ExposedNetworkManager : public omush::NetworkManager {
 public:
  int getServerCount() {
    return servers_.size();
  }

  IServer* getServerAtIndex(int index) {
    return servers_[index].get();
  }
};

class NetworkManagerTest : public testing::Test {
 protected:
  ExposedNetworkManager network_;
};

class MockServer : public IServer {
 public:
  MockServer() { polledTimes = 0; }

  void poll() override {
    ++polledTimes;
  }

  int polledTimes;
};

TEST_F(NetworkManagerTest, AddServerMethodIsAvailable) {
  EXPECT_EQ(network_.getServerCount(), 0);
  EXPECT_EQ(network_.addServer(new MockServer()), true);
  EXPECT_EQ(network_.getServerCount(), 1);
  EXPECT_EQ(network_.addServer(new MockServer()), true);
  EXPECT_EQ(network_.getServerCount(), 2);
}


TEST_F(NetworkManagerTest, PollRunsPollOnAddedServers) {
  network_.addServer(new MockServer());
  network_.addServer(new MockServer());
  MockServer* s0 = (MockServer*) network_.getServerAtIndex(0);
  MockServer* s1 = (MockServer*) network_.getServerAtIndex(1);

  EXPECT_EQ(s0->polledTimes, 0);
  EXPECT_EQ(s1->polledTimes, 0);

  network_.poll();
  EXPECT_EQ(s0->polledTimes, 1);

  for (int i = 0; i < 3; ++i) {
    network_.poll();
  }
  EXPECT_EQ(s0->polledTimes, 4);
  EXPECT_EQ(s1->polledTimes, 4);
}
