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
    server_ = new omush::WebSocketServer(9999);
  }

  virtual void TearDown() {
    delete server_;
  }
};

TEST_F(SocketServerTest, WebSocketServerPortReturnsCorrectPort) {
  int port = 9999;

  omush::ISocketServer* server = new omush::WebSocketServer(port);
  ASSERT_EQ(port, server->getPort());
  delete server;
}

TEST_F(SocketServerTest, WebSocketStartListeningDiesIfAlreadyListening) {
  server_->startListening();
  ASSERT_DEATH(server_->startListening(), "");
}


TEST_F(SocketServerTest, WebSocketCanNotPollWhenListenerNotStarted) {
  ASSERT_DEATH(server_->poll(), "");

  server_->startListening();
  server_->poll();
}
