/**
 * \file gametimer.h
 *
 * Copyright 2016 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_TIMER_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_TIMER_H_

#include "framework/igametimer.h"
#include <chrono>

namespace omush {
  class Timer : public ITimer {
   public:
    explicit Timer();
    void sleep() override;
    void start(unsigned int cylceTimeInNanoseconds) override;

   private:
    typedef std::chrono::high_resolution_clock hrc;
    /**
     * Duration of each loop of the timer.
     */
    std::chrono::nanoseconds loopNanoSeconds_;
    
    /**
     * The current time of the loop.
     */
    hrc::time_point thisTime_;
    
    /**
     * The time of the last loop.
     */
    hrc::time_point lastTime_;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_TIMER_H_
