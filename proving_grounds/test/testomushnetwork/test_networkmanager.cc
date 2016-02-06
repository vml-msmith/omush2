#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "include/omushnetwork/networkmanager.h"
#include "include/omushnetwork/isocketserver.h"

class NetworkManagerTest : public ::testing::Test {
 public:
  NetworkManagerTest() {
  }

  ~NetworkManagerTest() {
  }


  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

using namespace omush::network;

class MockWebServer : public ISocketServer {
 public:
  int getPort() override {
    return 0;
  }

  void startListening(unsigned int port) override {
  }

  MOCK_METHOD0(poll, void());
  MOCK_METHOD1(getNextMessage, bool(NetworkPacketDescriptorPair *));
};


TEST_F(NetworkManagerTest, PollCallsPollOnServers) {
  INetworkManager *manager = new NetworkManager();

  MockWebServer *server = new MockWebServer();
  MockWebServer *serverTwo = new MockWebServer();
  manager->addServer(server);
  manager->addServer(serverTwo);
  EXPECT_CALL(*server, poll());
  EXPECT_CALL(*serverTwo, poll());
  manager->poll();
  delete server;
  delete serverTwo;
  delete manager;
}


TEST_F(NetworkManagerTest, GetNextMessageCallsOnServers) {
  INetworkManager *manager = new NetworkManager();
  MockWebServer *server = new MockWebServer();
  MockWebServer *serverTwo = new MockWebServer();
  manager->addServer(server);
  manager->addServer(serverTwo);
  EXPECT_CALL(*server, getNextMessage(testing::_))
    .WillOnce(testing::Return(false));
  EXPECT_CALL(*serverTwo, getNextMessage(testing::_))
    .WillOnce(testing::Return(false));

  NetworkPacketDescriptorPair message;
  manager->getNextMessage(&message);
  delete server;
  delete serverTwo;
  delete manager;
}
