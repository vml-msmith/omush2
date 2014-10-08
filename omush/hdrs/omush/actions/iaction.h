/**
 * \file iaction.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_IACTION_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_IACTION_H_

#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {
    /**
     * Interface for all Action classes to implement.
     */
    class IAction {
     public:
      /**
       * Do the action items of the action. All setup methods per action must
       * be called before this action may succede. Implementations of this
       * method must verify that all setup methods have been called and all data
       * is valid before proceding.
       *
       * @param scope - ActionScope for the action.
       */
      virtual void enact(std::shared_ptr<ActionScope> scope) = 0;

      /**
       * Set the object that is doing the "looking".
       *
       * @param Object - Shared pointer to the DatabaseObject that is looking.
       */
      virtual void setEnactor(std::shared_ptr<IDatabaseObject> object) = 0;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_IACTION_H_
