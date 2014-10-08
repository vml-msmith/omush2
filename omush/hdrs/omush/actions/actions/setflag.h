/**
 * \file setflag.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_SETFLAG_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_SETFLAG_H_

#include "omush/actions/iaction.h"
#include <string>
#include "omush/scope.h"
#include "omush/database/databaseobject.h"
#include "omush/database/flag.h"


namespace omush {
  namespace actions {
    class SetFlag : public IAction {
     public:
      SetFlag();
      void setPlayer(std::shared_ptr<IDatabaseObject> object);
      void setTarget(std::shared_ptr<IDatabaseObject> object);
      void setValue(std::string value);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      std::shared_ptr<IDatabaseObject> player_;
      std::shared_ptr<IDatabaseObject> target_;
      std::string value_;

      void setFlagOnTarget(Flag *flag, std::shared_ptr<ActionScope> scope);

      void unsetFlagOnTarget(Flag *flag, std::shared_ptr<ActionScope> scope);
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_SETFLAG_H_
