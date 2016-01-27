#include "gtest/gtest.h"
#include "websocketserver.h"

class SocketServerTest : public ::testing::Test {
 protected:
  SocketServerTest() {
  }
  ~SocketServerTest() {
  }
};


TEST_F(SocketServerTest, ISocketServerExists) {
  // Test for the existance of a web socket server that can be created.
  omush::ISocketServer* server = new omush::ISocketServer();
  delete server;
}

TEST_F(SocketServerTest, WebSocketServerExists) {
  // Test for the existance of a web socket server that can be created.
  omush::ISocketServer* server = new omush::WebSocketServer();
  delete server;
}
