/**
 * \file test_timer.cc
 *
 * Copyright 2016 Michael Smith
 */

#include <ctime>
#include "gtest/gtest.h"
#include "framework/timer.h"
#include "development/measure.h"

class TimerTest : public ::testing::Test {
};


TEST_F(TimerTest, TimerWaitsApprorateTime) {
  int sleepNanoSeconds = 1000000;
  omush::ITimer *timer = new omush::Timer();
  timer->start(sleepNanoSeconds);
  auto func = [] (omush::ITimer *t) { t->sleep(); };
  std::chrono::milliseconds::rep firstLoopExecuteTime =
    omush::devel::measure<>::execution(func, timer);
  std::chrono::milliseconds::rep secondLoopExecuteTime =
    omush::devel::measure<>::execution(func, timer);

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
