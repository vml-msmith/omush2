/**
 * \file test_websocketserver.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "omush/network/websocketserver.h"

class TestWebSocketServer : public testing::Test {
 protected:
  omush::WebSocketServer server_;
};
