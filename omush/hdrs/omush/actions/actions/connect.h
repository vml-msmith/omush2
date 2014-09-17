/**
 * \file connect.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_CONNECT_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_CONNECT_H_

#include "omush/actions/iaction.h"
#include "omush/scope.h"
#include "omush/database/databaseobject.h"

namespace omush {
  namespace actions {
    class Connect : public IAction {
     public:
      Connect();
      void setPlayer(std::shared_ptr<IDatabaseObject> object);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      std::shared_ptr<IDatabaseObject> player_;
    };
  }  // namesapce actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_CONNECT_H_
