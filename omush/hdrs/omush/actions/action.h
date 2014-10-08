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

    /**
     * Superclass for all Action classes to derive from.
     *
     * Takes care of common code that all actions will need to use.
     */
    class Action : public IAction {
     protected:
      /**
       * Register a map of std::string => library::OString with Strings library.
       *
       * @param strings - map of std::string => library::OString to register.
       */
      void registerStrings_(Strings::ReplaceMap strings) {
        for (auto& item : strings) {
          Strings::addStringIfNotPresent(item.first, item.second);
        }
      }
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTION_H_
