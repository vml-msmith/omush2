/**
 * \file move.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/move.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/log.h"
#include "omush/database/utilities.h"
#include "omush/actions/actions/leave.h"
#include "omush/actions/actions/arrive.h"

namespace omush {
  namespace actions {
    Move::Move() {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
      setTarget(nullptr);
      setNewLocation(nullptr);

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

    void Move::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    void Move::setNewLocation(std::shared_ptr<IDatabaseObject> object) {
      newLocation_ = object;
    }

    bool Move::hasPermission_(std::shared_ptr<ActionScope> scope) {
      return true;
    }

    void Move::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::Move called without an enactor.");
        return;
      }

      if (target_ == NULL || target_ == nullptr) {
        library::log("action::Move called without a target.");
        return;
      }

      if (newLocation_ == NULL || newLocation_ == nullptr) {
        library::log("action::Move called without a new location.");
        return;
      }

      actions::Leave leave;
      leave.setEnactor(enactor_);
      leave.setTarget(target_);
      leave.enact(scope);

      std::shared_ptr<IDatabaseObject> currentLocation;
      target_->getLocation(currentLocation);

      if (currentLocation != nullptr) {
        currentLocation->removeContent(target_);
      }

      target_->setLocation(newLocation_);
      newLocation_->addContent(target_);

      actions::Arrive arrive;
      arrive.setEnactor(enactor_);
      arrive.setTarget(target_);
      arrive.enact(scope);
    }

  }  // namespace actions
}  // namespace omush
