/**
 * \file igamebuilder.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMEBUILDER_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMEBUILDER_H_

namespace omush {
  class IGameBuilder {
   public:
    IGameBuilder() {}
    virtual bool setupNetwork() const = 0;
   private:
  };
}  // omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMEBUILDER_H_
