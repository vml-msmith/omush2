/**
 * \file move.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_MOVE_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_MOVE_H_

#include "omush/actions/action.h"
#include <string>
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {
    class Move : public Action {
     public:
      Move();
      void setTarget(std::shared_ptr<IDatabaseObject> object);
      void setNewLocation(std::shared_ptr<IDatabaseObject> object);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      bool hasPermission_(std::shared_ptr<ActionScope> scope);
      std::shared_ptr<IDatabaseObject> target_;
      std::shared_ptr<IDatabaseObject> newLocation_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_MOVE_H_
