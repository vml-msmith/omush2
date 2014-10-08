/**
 * \file action.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTION_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTION_H_

#include "omush/actions/iaction.h"
#include "omush/framework/strings.h"

namespace omush {
  namespace actions {
    class Action : public IAction {
     protected:
      void registerStrings_(Strings::ReplaceMap strings) {
        for (auto& item : strings) {
          Strings::addStringIfNotPresent(item.first, item.second);
        }
      }
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTION_H_
