/**
 * \file set.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/set.h"

#include <memory>
#include <string>
#include <vector>
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/framework/strings.h"
#include "omush/database/databaseobject.h"
#include "omush/database/databasematcher.h"
#include "omush/notifier.h"
#include "omush/actions/actions/setflag.h"
#include "omush/actions/actions/setattribute.h"


namespace omush {
  namespace command {
    SetDefinition::SetDefinition() {
    }

    std::string SetDefinition::name() {
      return "@SET";
    }

    std::unique_ptr<ICommand> SetDefinition::factory() {
      return std::unique_ptr<ICommand>(new Set);
    }

    std::vector<std::string> SetDefinition::patterns() {
      std::vector<std::string> patterns;

      patterns.push_back("COMMAND_NAME (?P<object>[^=]+)=(?P<attribute>[^:]+):(?P<value>.+)");
      patterns.push_back("COMMAND_NAME (?P<object>[^=]+)=(?P<value>.+)");
      return patterns;
    }

    Set::Set() {
    }

    bool Set::execute(std::shared_ptr<CommandScope> scope) {
      std::shared_ptr<IDatabaseObject> enactor;
      if (!getEnactor_(scope, enactor)) {
        return true;
      }

      SetDefinition def;
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);

      std::string target = "";
      std::string value = "";

      std::map<std::string, std::string> args;
      unpackArgs_(scope, def, args);

      target = args["object"];
      value = args["value"];

      std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>> targetObjects(new std::vector<std::shared_ptr<IDatabaseObject>>);
      std::shared_ptr<IDatabaseObject> targetObject;
      if (DatabaseMatcher::findTargets(queueObject->gameInstance->database.get(),
                                       enactor,
                                       target,
                                       targetObjects)) {
       if (targetObjects->size() > 1) {
          // Too many.
          Notifier::notify(NULL,
                           enactor,
                           library::OString(Strings::get("Too many pattern matches")),
                           makeActionScope(scope));
        }
        else {

          if (args.find("attribute") == args.end()) {
            actions::SetFlag setAction;
            setAction.setEnactor(enactor);
            setAction.setTarget(targetObjects->front());
            setAction.setValue(value);
            setAction.enact(makeActionScope(scope));
          }
          else {
            actions::SetAttribute setAction;
            setAction.setEnactor(enactor);
            setAction.setTarget(targetObjects->front());
            setAction.setAttribute(args["attribute"]);
            setAction.setValue(value);
            setAction.enact(makeActionScope(scope));
          }

        }
      }
      else {
        Notifier::notify(NULL,
                         enactor,
                         library::OString(Strings::get("I don't see that here.")),
                         makeActionScope(scope));
      }


      return true;
    }

  }  // namespace command
}  // namespace omush
