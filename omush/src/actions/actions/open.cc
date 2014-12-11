/**
 * \file open.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/open.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/framework/strings.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/library/log.h"
#include "omush/database/nameformatter.h"
#include "omush/database/utilities.h"
#include "omush/actions/actions/move.h"
#include "omush/database/databasefactory.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionexit.h"

namespace omush {
  namespace actions {
    Open::Open() : name_("") {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
      setLocation(nullptr);
      target_ = nullptr;

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

    void Open::setName(std::string name) {
      name_ = name;
    }

    void Open::setLocation(std::shared_ptr<IDatabaseObject> location) {
      location_ = location;
    }

    void Open::getTarget(std::shared_ptr<IDatabaseObject> &target) {
      target = target_;
    }

    bool Open::hasPermission_(std::shared_ptr<ActionScope> scope) {
      return true;
    }

    void Open::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::Open called without an enactor.");
        return;
      }
      if (name_ == "") {
        library::log("action::Open called without a name.");
        return;
      }
      if (location_ == NULL || location_ == nullptr) {
        library::log("action::Open called without a location.");
        return;
      }

      std::shared_ptr<DatabaseObject> newObject;
      DatabaseFactory factory;
      factory.buildObject(DatabaseObjectDefinitionExit::getInstance(),
                          newObject);
      newObject->setName(name_);
      newObject->setDbref(scope->queueObject->gameInstance->database->getNextDbref());
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
      move.setNewLocation(location_);
      move.enact(scope);

      Notifier::notify(NULL,
                       enactor_,
                       library::OString("Created."),
                       scope);
      target_ = newObject;
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
