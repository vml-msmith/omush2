#include "gtest/gtest.h"
#include "framework/gametimer.h"

class SimpleTest : public ::testing::Test {
public:
};


TEST_F(SimpleTest, HaveGameTimer) {
  omush::IGameTimer *timer = new omush::GameTimer();
  delete timer;
  //  ASSERT_EQ(port, server_->getPort());
}

