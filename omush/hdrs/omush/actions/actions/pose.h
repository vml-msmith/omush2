/**
 * \file pose.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_POSE_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_POSE_H_

#include "omush/actions/action.h"
#include "omush/scope.h"
#include "omush/database/databaseobject.h"
#include "omush/library/string.h"

namespace omush {
  namespace actions {
    class Pose : public Action {
     public:
      Pose();
      void setPlayer(std::shared_ptr<IDatabaseObject> object);
      void setText(std::string text);
      library::OString makeString(std::shared_ptr<IDatabaseObject> object);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      std::shared_ptr<IDatabaseObject> player_;
      std::string text_;
      std::shared_ptr<ActionScope> scope_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_POSE_H_
