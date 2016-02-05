#include <ctime>
#include "gtest/gtest.h"
#include "framework/timer.h"

class TimerTest : public ::testing::Test {
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

TEST_F(TimerTest, TimerWaitsApprorateTime) {
  int sleepNanoSeconds = 1000000;
  omush::ITimer *timer = new omush::Timer();
  timer->start(sleepNanoSeconds);
  auto func = [] (omush::ITimer *t) { t->sleep(); };
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

TEST_F(TimerTest, CallSleepBeforeStartWillNotBreak) {
  omush::ITimer *timer = new omush::Timer();
  timer->sleep();
  delete timer;
}
