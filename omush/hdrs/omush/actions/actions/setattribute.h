/**
 * \file setattribute.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_SETATTRIBUTE_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_SETATTRIBUTE_H_

#include "omush/actions/action.h"
#include <string>
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {
    class SetAttribute : public Action {
     public:
      SetAttribute();
      void setValue(std::string value);
      void setAttribute(std::string attribute);
      void setTarget(std::shared_ptr<IDatabaseObject> target);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      bool hasPermission_(std::shared_ptr<ActionScope> scope);
      std::string attribute_;
      std::string value_;
      std::shared_ptr<IDatabaseObject> target_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_SETATTRIBUTE_H_
