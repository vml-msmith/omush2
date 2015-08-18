/**
 * \file actionsystem.h
 *
 * Copyright 2015 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONSYSTEM_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONSYSTEM_H_

//#include "omush/actions/iaction.h"
//#include "omush/framework/strings.h"
#include "omush/actions/actions/go.h"

namespace omush {
  namespace actions {
    class IActionSystem {
    };

    /**
     * Superclass for all Action classes to derive from.
     *
     * Takes care of common code that all actions will need to use.
     */
    class ActionSystem : public IActionSystem {
     public:
      template <class T>
      void provision(std::shared_ptr<actions::Action> &a) {
        a = std::shared_ptr<actions::Action>(new T());
      }


    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONSYSTEM_H_
