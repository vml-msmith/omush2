/**
 * \file iaction.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_IACTION_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_IACTION_H_

#include "omush/scope.h"

namespace omush {
  namespace actions {
    class IAction {
    public:
      virtual void enact(std::shared_ptr<ActionScope> scope) = 0;
    };
  }  // namesapce actions
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_IACTION_H_
