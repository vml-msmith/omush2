#include "gtest/gtest.h"
#include "websocketserver.h"

class SocketServerTest : public ::testing::Test {
 protected:
  SocketServerTest() {
  }
  ~SocketServerTest() {
  }
};

TEST_F(SocketServerTest, WebSocketServerPortReturnsCorrectPort) {
  int port = 9999;

  omush::ISocketServer* server = new omush::WebSocketServer(port);
  ASSERT_EQ(port, server->getPort());
  delete server;
}

TEST_F(SocketServerTest, WebSocketHasStartListeningMethod) {
  int port = 9999;

  omush::ISocketServer* server = new omush::WebSocketServer(port);
  server->startListening();

  delete server;
}


TEST_F(SocketServerTest, WebSocketCanNotPollWhenListenerNotStarted) {
  int port = 9999;

  omush::ISocketServer* server = new omush::WebSocketServer(port);
  ASSERT_DEATH(server->poll(), "");

  server->startListening();
  server->poll();

  delete server;
}
