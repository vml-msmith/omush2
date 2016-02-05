/**
 * \file itimer.h
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
     * Sleep the current thread for the remainder of the time in current loop.
     *
     * The duration that is slept is at LEAST as long as the difference between
     * the end of the last call to sleep() or the last call to start(),
     * whichever is greater.
     *
     * Note: The thread sleep routines can not gurantee that the thread will
     * sleep for exactly the specified time due to the OS having control of 
     * it's own resource. All this method gurantees is that we will sleep for
     * at LEAST the time specified. In practice, this turns out to be pretty
     * consistent under 1 millisecond. For example: Looping for 1 millisecond
     * will generally get you 1 millisecond. Sleeping for 10000 nanoseconds will
     * get you beween 10000 and 20000 nanoseconds.
     */
    virtual void sleep() = 0;

    /**
     * Start the timer with a loop duration specified.
     *
     * \param - unsigned int
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
