#include "gtest/gtest.h"
#include "gtest/gmock.h"
#include "websocketserver.h"
#include "common.h"

class SocketServerTest : public ::testing::Test {
 public:
  SocketServerTest() {
  }

  ~SocketServerTest() {
  }

  omush::ISocketServer* server_;

  virtual void SetUp() {
    server_ = new omush::WebSocketServer();
  }

  virtual void TearDown() {
    delete server_;
  }
};

class MockWebSocketServer : public omush::WebSocketSever {
  void mockAddMessage() {

  }
};

TEST_F(SocketServerTest, PortReturnsCorrectPort) {
  int port = 9999;
  server_->startListening(port);
  ASSERT_EQ(port, server_->getPort());
}

TEST_F(SocketServerTest, StartListeningDiesIfAlreadyListening) {
  server_->startListening(9999);
  ASSERT_DEATH(server_->startListening(9999), "");
}

TEST_F(SocketServerTest, CanNotPollWhenListenerNotStarted) {
  ASSERT_DEATH(server_->poll(), "");

  server_->startListening(9999);
  server_->poll();
}

TEST_F(SocketServerTest, GetNextMessageReturnsFalseWithNoMessagesInbuffer) {
  omush::NetworkPacketDescriptorPair message;
  ASSERT_FALSE(server_->getNextMessage(message));
}

TEST_F(SocketServerTest, GetNextMessageReturnsTrueWithMessageInbuffer) {
  omush::NetworkPacketDescriptorPair message;
  ASSERT_TRUE(server_->getNextMessage(message));
}
