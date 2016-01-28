#include "gtest/gtest.h"
#include "websocketserver.h"

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

TEST_F(SocketServerTest, WebSocketServerPortReturnsCorrectPort) {
  int port = 9999;
  server_->startListening(port);
  ASSERT_EQ(port, server_->getPort());
}

TEST_F(SocketServerTest, WebSocketStartListeningDiesIfAlreadyListening) {
  server_->startListening(9999);
  ASSERT_DEATH(server_->startListening(9999), "");
}

TEST_F(SocketServerTest, WebSocketCanNotPollWhenListenerNotStarted) {
  ASSERT_DEATH(server_->poll(), "");

  server_->startListening(9999);
  server_->poll();
}
