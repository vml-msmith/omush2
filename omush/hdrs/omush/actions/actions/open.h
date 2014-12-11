/**
 * \file open.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_OPEN_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_OPEN_H_

#include "omush/actions/action.h"
#include <string>
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {
    class Open : public Action {
     public:
      Open();
      void setName(std::string name);
      void setLocation(std::shared_ptr<IDatabaseObject> location);
      void getTarget(std::shared_ptr<IDatabaseObject> &target);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      bool hasPermission_(std::shared_ptr<ActionScope> scope);
      std::string name_;
      std::shared_ptr<IDatabaseObject> location_;
      std::shared_ptr<IDatabaseObject> target_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_OPEN_H_
