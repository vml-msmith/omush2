/**
 * \file powerrevoke.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/powerrevoke.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/framework/strings.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/library/log.h"
#include "omush/database/nameformatter.h"

namespace omush {
  namespace actions {
    PowerRevoke::PowerRevoke() : target_(nullptr) {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
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

    void PowerRevoke::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    void PowerRevoke::setPowerString(std::string powerString) {
    }

    void PowerRevoke::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::Look called without an enactor.");
        return;
      }

      if (target_ == NULL || target_ == nullptr) {
        library::log("action::Look called without a target.");
        return;
      }

      library::string::OString lines = library::OString("");

      Notifier::notify(NULL, enactor_, lines, scope);
    }


  }  // namespace actions
}  // namespace omush
