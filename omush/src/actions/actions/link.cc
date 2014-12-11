/**
 * \file link.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/link.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/framework/strings.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/library/log.h"
#include "omush/database/nameformatter.h"
#include "omush/database/utilities.h"

namespace omush {
  namespace actions {
    Link::Link() {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
      setTarget(nullptr);
      setDestination(nullptr);

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

    void Link::setTarget(std::shared_ptr<IDatabaseObject> target) {
      target_ = target;
    }

    void Link::setDestination(std::shared_ptr<IDatabaseObject> destination) {
      destination_ = destination;
    }

    bool Link::hasPermission_(std::shared_ptr<ActionScope> scope) {
      return true;
    }

    void Link::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::Link called without an enactor.");
        return;
      }

      if (target_ == NULL || target_ == nullptr) {
        library::log("action::Link called without a target.");
        return;
      }

      if (destination_ == NULL || destination_ == nullptr) {
        library::log("action::Link called without a destination.");
        return;
      }

      target_->setHome(destination_);

      Notifier::notify(NULL,
                       enactor_,
                       library::OString("Linked."),
                       scope);
    }

  }  // namespace actions
}  // namespace omush
