/**
 * \file powerrevoke.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_POWERREVOKE_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_POWERREVOKE_H_

#include "omush/actions/action.h"
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {
    class PowerRevoke : public Action {
     public:
      PowerRevoke();
      void setTarget(std::shared_ptr<IDatabaseObject> object);
      void setPowerString(std::string powerString);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      std::shared_ptr<IDatabaseObject> target_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_POWERREVOKE_H_
