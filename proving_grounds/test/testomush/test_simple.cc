#include "gtest/gtest.h"
#include "framework/gametimer.h"
#include <ctime>

class SimpleTest : public ::testing::Test {
public:
};

template<typename TimeT = std::chrono::nanoseconds>
struct measure
{
  template<typename F, typename ...Args>
  static typename TimeT::rep execution(F&& func, Args&&... args)
  {
    auto start = std::chrono::system_clock::now();
    std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
    auto duration = std::chrono::duration_cast< TimeT>
    (std::chrono::system_clock::now() - start);
    return duration.count();
  }
};

TEST_F(SimpleTest, GameTimerWaitsApprorateTime) {
  int sleepNanoSeconds = 1000000;
  omush::IGameTimer *timer = new omush::GameTimer();
  timer->start(sleepNanoSeconds);
  auto func = [] (omush::IGameTimer *t) { t->sleep(); };
  std::chrono::milliseconds::rep firstLoopExecuteTime =
    measure<>::execution(func, timer);
  std::chrono::milliseconds::rep secondLoopExecuteTime =
    measure<>::execution(func, timer);

  ASSERT_GT(firstLoopExecuteTime, sleepNanoSeconds);
  ASSERT_LT(firstLoopExecuteTime, sleepNanoSeconds * 2);
  ASSERT_GT(secondLoopExecuteTime, sleepNanoSeconds);
  ASSERT_LT(secondLoopExecuteTime, sleepNanoSeconds * 2);
  delete timer;
}


TEST_F(SimpleTest, CallSleepBeforeStartWillNotBreak) {
  omush::IGameTimer *timer = new omush::GameTimer();
  timer->sleep();
  delete timer;
}