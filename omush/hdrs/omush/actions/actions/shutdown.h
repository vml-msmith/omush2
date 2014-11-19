/**
 * \file shutdown.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_SHUTDOWN_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_SHUTDOWN_H_

#include "omush/actions/action.h"
#include <string>
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"
#include "omush/library/string.h"

namespace omush {
  namespace actions {
    class Shutdown : public Action {
     public:
      Shutdown();
      void enact(std::shared_ptr<ActionScope> scope) override;
      void setReboot(bool isReboot);
      library::OString makeString(std::shared_ptr<IDatabaseObject> object);
     private:
      bool isReboot_;
      bool hasPermission_(std::shared_ptr<ActionScope> scope);
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_SHUTDOWN_H_
