#include "gtest/gtest.h"
#include "include/omushnetwork/networkmanager.h"

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


TEST_F(NetworkManagerTest, SimpleTest) {
  omush::network::INetworkManager *manager = new omush::network::NetworkManager();
}
