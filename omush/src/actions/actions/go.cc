/**
 * \file go.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/go.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/log.h"
#include "omush/database/utilities.h"
#include "omush/actions/actions/move.h"

namespace omush {
  namespace actions {
    Go::Go() {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
      setTarget(nullptr);

      if (hasAddedStrings == false) {
        Strings::ReplaceMap items;
        /*
        items["ACTION_CONNECT__YOU_HAVE_CONNECTED"] =
          "You have connected...";
        items["ACTION_CONNECT__OTHER_HAS_CONNECTED"] =
          "!playerName has connected.";
        */
        registerStrings_(items);
      }
    }

    void Go::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    bool Go::hasPermission_(std::shared_ptr<ActionScope> scope) {
      return true;
    }

    void Go::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::Move called without an enactor.");
        return;
      }

      if (target_ == NULL || target_ == nullptr) {
        library::log("action::Move called without a target.");
        return;
      }

      std::shared_ptr<IDatabaseObject> newLocation;
      target_->getHome(newLocation);

      actions::Move move;
      move.setEnactor(enactor_);
      move.setTarget(enactor_);
      move.setNewLocation(newLocation);
      move.enact(scope);
    }

  }  // namespace actions
}  // namespace omush
