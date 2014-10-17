/**
 * \file think.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_THINK_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_THINK_H_

#include "omush/actions/action.h"
#include "omush/scope.h"
#include "omush/database/databaseobject.h"
#include "omush/library/string.h"

namespace omush {
  namespace actions {
    class Think : public Action {
     public:
      Think();
      void setPlayer(std::shared_ptr<IDatabaseObject> object);
      void setText(library::OString text);
      void enact(std::shared_ptr<ActionScope> scope) override;
     private:
      std::shared_ptr<IDatabaseObject> player_;
      library::OString text_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_Think_H_
