/**
 * \file dig.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_DIG_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_DIG_H_

#include "omush/actions/action.h"
#include <string>
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {
    class Dig : public Action {
     public:
      Dig();
      void setName(std::string name);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      bool hasPermission_(std::shared_ptr<ActionScope> scope);
      std::string name_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_DIG_H_
