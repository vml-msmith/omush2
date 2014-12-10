/**
 * \file create.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_CREATE_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_CREATE_H_

#include "omush/actions/action.h"
#include <string>
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {
    class Create : public Action {
     public:
      Create();
      void setName(std::string name);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      bool hasPermission_(std::shared_ptr<ActionScope> scope);
      /*
      void notifyEnactor_(std::shared_ptr<ActionScope> scope,
                          Power* power);
      void notifyTarget_(std::shared_ptr<ActionScope> scope,
                         Power* power);
      bool hasPermission_(std::shared_ptr<ActionScope> scope,
                          Power* power, int level);

      std::shared_ptr<IDatabaseObject> target_;

      std::string powerString_;
      int powerLevel_;
      */
      std::string name_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_CREATE_H_
