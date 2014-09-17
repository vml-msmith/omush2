/**
 * \file connect.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/connect.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
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

    void Connect::enact(std::shared_ptr<ActionScope> scope) {
      //      scope->queueObject->gameInstance->game->sendNetworkMessageByDescriptor(scope->queueObject->descId,
      //                                                                     "Hello " + player_->getName() + "!");
      // Notify player he's connected.
      // Notify other objects in room he's connected.
      // Notify room he's connected.
      // Trigger aconnect on object.
      // Trigger aconnect on room
      // Trigger aconnect on global objects?
      // Action Look
      Notifier::notify(NULL, player_, library::string::OString("You have connected..."), scope);


      // Get the room.
      std::shared_ptr<IDatabaseObject> object = nullptr;
      player_->getLocation(object);
      //      if (scope->queueObject->gameInstance->database->getObjectByUUID(scope->queueObject->executor,
      actions::Look lookAction;
      lookAction.setPlayer(player_);
      lookAction.setTarget(object);
      lookAction.enact(scope);
    }

  }  // namespace actions
}  // namespace omush
