/**
 * \file arrive.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/arrive.h"
// TODO(msmith): remove boost dependency.
#include <boost/bind.hpp>

#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/log.h"
#include "omush/notifier.h"
#include "omush/database/utilities.h"
#include "omush/library/string.h"
#include "omush/database/nameformatter.h"
#include "omush/actions/actions/look.h"

namespace omush {
  namespace actions {
    Arrive::Arrive() {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
      setTarget(nullptr);

      if (hasAddedStrings == false) {
        Strings::ReplaceMap items;
        items["ACTION_ARRIVE__YOU_HAVE_ARRIVED"] =
          "You have arrived...";
        items["ACTION_ARRIVE__OTHER_HAS_ARRIVED"] =
          "!name has arrived.";
        registerStrings_(items);
      }
    }

    void Arrive::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    bool Arrive::hasPermission_(std::shared_ptr<ActionScope> scope) {
      return true;
    }

    library::OString Arrive::hasArrivedString(
      std::shared_ptr<IDatabaseObject> object) {
      if (object == target_) {
        return Strings::get("ACTION_ARRIVE__YOU_HAVE_ARRIVED",
                            scope_);
      }

      Strings::ReplaceMap replacements;
      library::OString name;
      NameFormatter::format(scope_,
                            object,
                            target_,
                            0,
                            name);

      replacements["!name"] = name;
      return Strings::get("ACTION_ARRIVE__OTHER_HAS_ARRIVED",
                          scope_,
                          replacements);
    }

    void Arrive::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::Arrive called without an enactor.");
        return;
      }

      if (target_ == NULL || target_ == nullptr) {
        library::log("action::Arrive called without a target.");
        return;
      }

      scope_ = scope;

      Notifier::notifySurroundings(
          NULL,
          target_,
          boost::bind(&omush::actions::Arrive::hasArrivedString,
                      this,
                      ::_1),
          scope);

std::shared_ptr<IDatabaseObject> location;
target_->getLocation(location);
          actions::Look lookAction;
          lookAction.setEnactor(target_);
          lookAction.setTarget(location);
          lookAction.enact(scope);

    }

  }  // namespace actions
}  // namespace omush
