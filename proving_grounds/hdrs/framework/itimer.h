/**
 * \file igametimer.h
 *
 * Copyright 2016 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_ITIMER_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_ITIMER_H_


namespace omush {
  class ITimer {
  public:
    /**
     * Default constructor.
     */
    explicit ITimer(int);

    /**
     *
     */
    virtual void sleep() = 0;
    
    /**
     *
     */
    virtual void start(unsigned int cylceTimeInNanoseconds) = 0;
    
    /**
     *
     */
    virtual ~ITimer() {};
  protected:
    ITimer() {};
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_ITIMER_H_
