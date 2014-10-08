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

#include "omush/notifier.h"
#include "omush/library/string.h"

#include "omush/actions/actions/look.h"

namespace omush {
  namespace actions {
    Connect::Connect() {
    }

    void Connect::setPlayer(std::shared_ptr<IDatabaseObject> object) {
      player_ = object;
    }


    library::OString Connect::playerHasConnectedString(
        std::shared_ptr<IDatabaseObject> object) {
     if (object == player_)
        return library::OString("You have connected...");

      // TODO(msmith): Format this name.
      return library::OString(player_->getName() + " has connected.");
    }

    void Connect::enact(std::shared_ptr<ActionScope> scope) {
      if (player_ == NULL || player_ == nullptr)
        return;

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
      lookAction.setPlayer(player_);
      lookAction.setTarget(object);
      lookAction.enact(scope);
    }

  }  // namespace actions
}  // namespace omush
