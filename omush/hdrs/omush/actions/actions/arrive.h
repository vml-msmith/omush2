/**
 * \file arrive.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_ARRIVE_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_ARRIVE_H_

#include "omush/actions/action.h"
#include <string>
#include "omush/library/string.h"
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {
    class Arrive : public Action {
     public:
      Arrive();
      void setTarget(std::shared_ptr<IDatabaseObject> object);
      void enact(std::shared_ptr<ActionScope> scope) override;
      library::OString hasArrivedString(std::shared_ptr<IDatabaseObject> object);
     private:
      bool hasPermission_(std::shared_ptr<ActionScope> scope);
      std::shared_ptr<IDatabaseObject> target_;
      std::shared_ptr<IDatabaseObject> newLocation_;
      std::shared_ptr<ActionScope> scope_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_ARRIVE_H_
