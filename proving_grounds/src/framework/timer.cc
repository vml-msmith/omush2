/**
 * \file gametimer.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "framework/gametimer.h"
#include <thread>

// DEBUG:
#include <stdio.h>
#include <iostream>

namespace omush {
  /**
   * Initially set loopNanoSeconds_ to 0 so that calling sleep() without first
   * calling start() will not break anything. It'll just sleep for 0
   * nanoseconds.
   */
  Timer::Timer() {
    this->loopNanoSeconds_ = std::chrono::nanoseconds(0);
  }

  void Timer::start(unsigned int cylceTimeInNanoseconds) {
    loopNanoSeconds_ = std::chrono::nanoseconds(cylceTimeInNanoseconds);
    thisTime_ = std::chrono::high_resolution_clock::now();
    lastTime_ = this->thisTime_;;
  }

  void Timer::sleep() {
    this->thisTime_ = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds duration = this->thisTime_ - this->lastTime_;
    if (duration < this->loopNanoSeconds_) {
      std::chrono::nanoseconds sleep_time =
      (this->loopNanoSeconds_ - duration);
      std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_time));
    }

    this->thisTime_ = std::chrono::high_resolution_clock::now();
    this->lastTime_ = this->thisTime_;
  }
}  // namespace omush
