/**
 * \file look.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LOOK_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LOOK_H_

#include "omush/actions/iaction.h"
#include "omush/scope.h"
#include "omush/database/databaseobject.h"

namespace omush {
  namespace actions {
    class Look : public IAction {
     public:
      Look();
      void setPlayer(std::shared_ptr<IDatabaseObject> object);
      void setTarget(std::shared_ptr<IDatabaseObject> object);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      std::shared_ptr<IDatabaseObject> player_;
      std::shared_ptr<IDatabaseObject> target_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LOOK_H_
