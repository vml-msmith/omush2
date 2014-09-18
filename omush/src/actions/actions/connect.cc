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
#include <boost/bind.hpp>

namespace omush {
  namespace actions {
    Connect::Connect() {
    }

    void Connect::setPlayer(std::shared_ptr<IDatabaseObject> object) {
      player_ = object;
    }


    library::OString Connect::connectString(std::shared_ptr<IDatabaseObject> object) {
      if (object == player_)
        return library::OString("You have connected...");

      // TODO(msmith): Format this name.
      return library::OString(player_->getName() + " has connected.");
    }

    void Connect::enact(std::shared_ptr<ActionScope> scope) {
      // Trigger aconnect on object.
      // Trigger aconnect on room
      // Trigger aconnect on global objects?
      Notifier::notifySurroundings(NULL,
                                   player_,
                                   boost::bind(&omush::actions::Connect::connectString,
                                               this,
                                                 ::_1),
                                   scope);

      // Get the room.
      std::shared_ptr<IDatabaseObject> object = nullptr;
      player_->getLocation(object);
      actions::Look lookAction;
      lookAction.setPlayer(player_);
      lookAction.setTarget(object);
      lookAction.enact(scope);
    }

  }  // namespace actions
}  // namespace omush
