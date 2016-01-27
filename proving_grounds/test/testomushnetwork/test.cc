#include "gtest/gtest.h"
#include "isocketserver.h"

class MyTest : public ::testing::Test {
protected:
  MyTest() {
  };
  ~MyTest() {
  };
};


TEST_F(MyTest, ISocketServerExists) {
  // Test for the existance of a web socket server that can be created.
  omush::ISocketServer* server = new omush::ISocketServer();
  delete server;
}
