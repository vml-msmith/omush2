/**
 * \file open.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/open.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/strings.h"
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/actions/actions/open.h"
#include "omush/actions/actions/link.h"
#include "omush/functions/iexpressionengine.h"
#include "omush/database/databaseobject.h"
#include "omush/database/databasematcher.h"

namespace omush {
  namespace command {

    std::string OpenDefinition::name() {
      return "@OPEN";
    }

    std::unique_ptr<ICommand> OpenDefinition::factory() {
      return std::unique_ptr<ICommand>(new Open);
    }

    std::vector<std::string> OpenDefinition::getAliasList() {
      std::vector<std::string> alias;

      return alias;
    }

    std::vector<std::string> OpenDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("COMMAND_NAME (?P<name>[^=]+)=(?P<destination>[^,]+),(?P<recpName>[^,]+)");
      patterns.push_back("COMMAND_NAME (?P<name>[^=]+)=(?P<destination>[^,]+)");
      patterns.push_back("COMMAND_NAME (?P<name>[^=]+)");
      return patterns;
    }

    Open::Open() {
    }

    bool Open::openExit_(std::string name,
                         std::shared_ptr<IDatabaseObject> enactor,
                         std::shared_ptr<IDatabaseObject> location,
                         std::shared_ptr<CommandScope> scope,
                         std::shared_ptr<IDatabaseObject>& exit) {
      actions::Open openAction;
      openAction.setEnactor(enactor);
      openAction.setName(name);
      openAction.setLocation(location);
      openAction.enact(makeActionScope(scope));

      openAction.getTarget(exit);
      return (exit != nullptr);
    }

    bool Open::execute(std::shared_ptr<CommandScope> scope) {
      OpenDefinition def;
      std::map<std::string,std::string> args;
      _unpackArgs(scope, def, args);
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);
      std::shared_ptr<IDatabaseObject> enactor;
      if (!scope->
          queueObject->
          gameInstance->
          database->
          getObjectByUUID(scope->queueObject->executor,
                          enactor)) {
        return true;
      }


      std::shared_ptr<IDatabaseObject> location;
      enactor->getLocation(location);

      std::shared_ptr<IDatabaseObject> target;
      openExit_(args["name"],
                enactor,
                location,
                scope,
                target);

      if (args.find("destination") != args.end() && target != nullptr) {
        std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>> targetObjects(new std::vector<std::shared_ptr<IDatabaseObject>>);
        std::shared_ptr<IDatabaseObject> targetObject;
        if (DatabaseMatcher::findTargets(queueObject->gameInstance->database.get(),
                                         enactor,
                                         args["destination"],
                                         targetObjects)) {
          if (targetObjects->size() > 1) {
            // Too many.
            Notifier::notify(NULL,
                             enactor,
                             library::OString(Strings::get("I don't know where you want to link to.")),
                             makeActionScope(scope));
          }
          else {
            actions::Link linkAction;
            linkAction.setEnactor(enactor);
            linkAction.setTarget(target);
            linkAction.setDestination(targetObjects->front());
            linkAction.enact(makeActionScope(scope));

            if (args.find("recpName") != args.end()) {
              openExit_(args["recpName"],
                        enactor,
                        targetObjects->front(),
                        scope,
                        target);

              if (target != nullptr) {
                linkAction.setTarget(target);
                linkAction.setDestination(location);
                linkAction.enact(makeActionScope(scope));
              }
            }
          }
        }
        else {
          Notifier::notify(NULL,
                           enactor,
                           library::OString("I don't see that here."),

                           makeActionScope(scope));
        }
      }


      /*
      actions::Open action;
      action.setEnactor(enactor);
      action.setName(args["name"]);
      action.enact(makeActionScope(scope));
      */
      return true;
    }


  }  // namespace command
}  // namespace omush
