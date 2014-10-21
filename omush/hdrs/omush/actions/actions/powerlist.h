/**
 * \file powerlist.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_POWERLIST_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_POWERLIST_H_

#include "omush/actions/action.h"
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {
    class PowerList : public Action {
     public:
      PowerList();
      void setTarget(std::shared_ptr<IDatabaseObject> object);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      std::shared_ptr<IDatabaseObject> target_;
      /*
      void setFlagOnTarget(Flag *flag, std::shared_ptr<ActionScope> scope);

      void unsetFlagOnTarget(Flag *flag, std::shared_ptr<ActionScope> scope);
      */
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_POWERLIST_H_
