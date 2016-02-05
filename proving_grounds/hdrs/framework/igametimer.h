/**
 * \file igametimer.h
 *
 * Copyright 2016 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMETIMER_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMETIMER_H_


namespace omush {
  class IGameTimer {
  public:
    /**
     * Default constructor.
     */
    explicit IGameTimer(int);

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
    virtual ~IGameTimer() {};
  protected:
    IGameTimer() {};
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMETIMER_H_
