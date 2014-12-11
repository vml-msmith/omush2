/**
 * \file leave.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/leave.h"
// TODO(msmith): remove boost dependency.
#include <boost/bind.hpp>

#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/log.h"
#include "omush/notifier.h"
#include "omush/database/utilities.h"
#include "omush/library/string.h"
#include "omush/database/nameformatter.h"

namespace omush {
  namespace actions {
    Leave::Leave() {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
      setTarget(nullptr);

      if (hasAddedStrings == false) {
        Strings::ReplaceMap items;
        items["ACTION_LEAVE__YOU_HAVE_LEFT"] =
          "You leave.";
        items["ACTION_LEAVE__OTHER_HAS_LEFT"] =
          "!name has left.";
        registerStrings_(items);
      }
    }

    void Leave::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    bool Leave::hasPermission_(std::shared_ptr<ActionScope> scope) {
      return true;
    }

    library::OString Leave::hasLeftString(
      std::shared_ptr<IDatabaseObject> object) {
      if (object == target_) {
        return Strings::get("ACTION_LEAVE__YOU_HAVE_LEFT",
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
      return Strings::get("ACTION_LEAVE__OTHER_HAS_LEFT",
                          scope_,
                          replacements);
    }

    void Leave::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::Leave called without an enactor.");
        return;
      }

      if (target_ == NULL || target_ == nullptr) {
        library::log("action::Leave called without a target.");
        return;
      }

      scope_ = scope;
      /*
      Notifier::notifySurroundings(
          NULL,
          target_,
          boost::bind(&omush::actions::Arrive::hasLeftString,
                      this,
                      ::_1),
          scope);
      */
    }


  }  // namespace actions
}  // namespace omush
