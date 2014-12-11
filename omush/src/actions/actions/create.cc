/**
 * \file create.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/create.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/framework/strings.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/library/log.h"
#include "omush/database/nameformatter.h"
#include "omush/database/utilities.h"
#include "omush/database/databasefactory.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionthing.h"
#include "omush/actions/actions/move.h"

namespace omush {
  namespace actions {
    Create::Create() : name_("") {
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

    void Create::setName(std::string name) {
      name_ = name;
    }


    bool Create::hasPermission_(std::shared_ptr<ActionScope> scope) {
      return true;
    }

    void Create::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::Create called without an enactor.");
        return;
      }

      std::shared_ptr<DatabaseObject> newObject;
      DatabaseFactory factory;
      factory.buildObject(DatabaseObjectDefinitionThing::getInstance(),
                          newObject);
      newObject->setDbref(scope->
        queueObject->
        gameInstance->
        database->getNextDbref());
      newObject->setName(name_);
      // Must be he owner of the object!
      std::shared_ptr<IDatabaseObject> owner;
      enactor_->getOwner(owner);
      newObject->setOwner(owner);
      scope->
        queueObject->
        gameInstance->
        database->addObject(newObject);

      actions::Move move;
      move.setEnactor(enactor_);
      move.setTarget(newObject);
      move.setNewLocation(enactor_);
      move.enact(scope);

      Notifier::notify(NULL,
                       enactor_,
                       library::OString("Created."),
                       scope);
    }

    /*
    void PowerGrant::notifyEnactor_(std::shared_ptr<ActionScope> scope,
                                    Power* power) {
      std::string pName = scope->
        queueObject->
        gameInstance->
        database->powers.powerToName(power, powerLevel_);

      Notifier::notify(NULL,
                       enactor_,
                       library::OString(target_->getName() + " -- \"" + pName + "\" granted."),
                       scope);
    }
    */
  }  // namespace actions
}  // namespace omush
