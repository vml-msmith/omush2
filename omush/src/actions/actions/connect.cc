/**
 * \file connect.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/connect.h"
// TODO(msmith): remove boost dependency.
#include <boost/bind.hpp>

#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/framework/strings.h"
#include "omush/notifier.h"
#include "omush/actions/actions/look.h"
#include "omush/library/log.h"
#include "omush/library/string.h"
#include "omush/database/nameformatter.h"

namespace omush {
  namespace actions {
    Connect::Connect() : player_(nullptr) {
      static bool hasAddedStrings = false;

      if (hasAddedStrings == false) {
        Strings::ReplaceMap items;
        items["ACTION_CONNECT__YOU_HAVE_CONNECTED"] =
          "You have connected...";
        items["ACTION_CONNECT__OTHER_HAS_CONNECTED"] =
          "!playerName has connected.";
        registerStrings_(items);
      }
    }

    void Connect::setPlayer(std::shared_ptr<IDatabaseObject> object) {
      player_ = object;
    }

    library::OString Connect::playerHasConnectedString(
      std::shared_ptr<IDatabaseObject> object) {
      if (object == player_) {
        return Strings::get("ACTION_CONNECT__YOU_HAVE_CONNECTED",
                            scope_);
      }

      // TODO(msmith): Format this name.
      Strings::ReplaceMap replacements;
      library::OString name;
      NameFormatter::format(scope_,
                            object,
                            player_,
                            0,
                            name);

      replacements["!playerName"] = name;
      return Strings::get("ACTION_CONNECT__OTHER_HAS_CONNECTED",
                          scope_,
                          replacements);
    }

    void Connect::enact(std::shared_ptr<ActionScope> scope) {
      if (player_ == NULL || player_ == nullptr) {
        library::log("action::Connect called without an enactor.");
        return;
      }

      scope_ = scope;

      doTriggerAConnectObject_(scope);
      doTriggerAConnectLocation_(scope);
      doTriggerAConnectGlobal_(scope);
      doConnectNotify_(scope);
      doLook_(scope);
    }

    void Connect::doTriggerAConnectObject_(
        std::shared_ptr<ActionScope> scope) {
      // TODO(msmith): Implement.
    }

    void Connect::doTriggerAConnectLocation_(
        std::shared_ptr<ActionScope> scope) {
      // TODO(msmith): Implement.
    }

    void Connect::doTriggerAConnectGlobal_(
        std::shared_ptr<ActionScope> scope) {
      // TODO(msmith): Implement.
    }

    void Connect::doConnectNotify_(
        std::shared_ptr<ActionScope> scope) {
      Notifier::notifySurroundings(
          NULL,
          player_,
          boost::bind(&omush::actions::Connect::playerHasConnectedString,
                      this,
                      ::_1),
          scope);
    }

    void Connect::doLook_(std::shared_ptr<ActionScope> scope) {
      std::shared_ptr<IDatabaseObject> object = nullptr;
      player_->getLocation(object);
      actions::Look lookAction;
      lookAction.setEnactor(player_);
      lookAction.setTarget(object);
      lookAction.enact(scope);
    }

  }  // namespace actions
}  // namespace omush
