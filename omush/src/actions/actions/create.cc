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
      /*
      if (target_ == NULL || target_ == nullptr) {
        library::log("action::Create called without a target.");
        return;
      }
      */

      std::shared_ptr<DatabaseObject> newObject;
      DatabaseFactory factory;
      factory.buildObject(DatabaseObjectDefinitionThing::getInstance(),
                          newObject);
      newObject->setName(name_);

      // TODO(msmith): Abstract to a databasemove function.
      newObject->setLocation(enactor_);
      enactor_->addContent(newObject);
      scope->
        queueObject->
        gameInstance->
        database->addObject(newObject);

      Notifier::notify(NULL,
                       enactor_,
                       library::OString("Create the thing."),
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
