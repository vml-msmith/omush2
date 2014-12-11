/**
 * \file link.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LINK_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LINK_H_

#include "omush/actions/action.h"
#include <string>
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {
    class Link : public Action {
     public:
      Link();
      void setName(std::string name);
      void setTarget(std::shared_ptr<IDatabaseObject> target);
      void setDestination(std::shared_ptr<IDatabaseObject> destination);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      bool hasPermission_(std::shared_ptr<ActionScope> scope);
      std::shared_ptr<IDatabaseObject> destination_;
      std::shared_ptr<IDatabaseObject> target_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LINK_H_
