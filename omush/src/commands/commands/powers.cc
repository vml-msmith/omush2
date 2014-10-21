/**
 * \file powers.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/powers.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/strings.h"
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/actions/actions/powerlist.h"
#include "omush/actions/actions/powergrant.h"
#include "omush/actions/actions/powerrevoke.h"
#include "omush/functions/iexpressionengine.h"
#include "omush/database/databaseobject.h"
#include "omush/database/databasematcher.h"

#include <iostream>

namespace omush {
  namespace command {

    std::string PowersDefinition::name() {
      return "@POWERS";
    }

    std::unique_ptr<ICommand> PowersDefinition::factory() {
      return std::unique_ptr<ICommand>(new Powers);
    }

    std::vector<std::string> PowersDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("COMMAND_NAME(?P<throwaway> (?P<target>.+))?");
      patterns.push_back("COMMAND_NAME(?P<throwaway>/(?P<switch>add|remove)) (?P<target>.+)=(?P<power>.+)");
      return patterns;
    }

    Powers::Powers() {
    }

    bool Powers::_getTarget(std::shared_ptr<CommandScope> scope,
                            std::string targetString,
                            std::shared_ptr<IDatabaseObject> looker,
                            std::shared_ptr<IDatabaseObject> &target,
                            library::OString &error) {
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);
      std::shared_ptr<ActionScope> aScope = makeActionScope(scope);
      library::OString tempTarget = library::OString(targetString);
      scope->queueObject
        ->gameInstance
        ->expressionEngine
        ->parse(tempTarget, makeFunctionScope(aScope), tempTarget);

      targetString = tempTarget.plainText();

      if (targetString.length() == 0) {
        targetString = "me";
      }

      std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>
        targetObjects(new std::vector<std::shared_ptr<IDatabaseObject>>);

      if (DatabaseMatcher::findTargets(queueObject->
                                       gameInstance->
                                       database.get(),
                                       looker,
                                       targetString,
                                       targetObjects)) {
        if (targetObjects->size() > 1) {
          std::cout << "Too many" << std::endl;
          error = Strings::get("TARGET_MATCHER__TOO_MANY_MATCHES");
          return false;
        }
      }
      else {
        error = Strings::get("TARGET_MATCHER__NOT_FOUND");
        return false;
      }

      target = targetObjects->front();
      std::cout << "HerE" << std::endl;
      return true;
    }

    bool Powers::execute(std::shared_ptr<CommandScope> scope) {
      PowersDefinition def;
      std::map<std::string,std::string> args;
      _unpackArgs(scope, def, args);


      std::shared_ptr<IDatabaseObject> enactor;
      if (!scope->
          queueObject->
          gameInstance->
          database->
          getObjectByUUID(scope->queueObject->executor,
                          enactor)) {
        return true;
      }

      std::shared_ptr<IDatabaseObject> target = enactor;
      if (args.find("target") != args.end()) {
        std::shared_ptr<IDatabaseObject> looker;
        scope->queueObject->getExecutorObject(looker);
        library::OString errorString;
        std::string targetString = args["target"];
        if (!_getTarget(scope,
                        targetString,
                        looker,
                        target,
                        errorString)) {
          Notifier::notify(NULL,
                           looker,
                           errorString,
                           makeActionScope(scope));
          return true;
        }
      }


      if (args.find("power") == args.end()) {
        actions::PowerList action;
        action.setEnactor(enactor);
        action.setTarget(target);
        action.enact(makeActionScope(scope));
        // Power list
      }
      else {
        std::string switchString = "add";
        if (args.find("switch") == args.end()) {
          switchString = args["switch"];
        }

        if (library::string::iequals(switchString, "add")) {
            actions::PowerGrant action;
            action.setEnactor(enactor);
            action.setTarget(target);
            action.setPowerString(args["power"]);
            action.enact(makeActionScope(scope));
        }
        else {
            actions::PowerRevoke action;
            action.setEnactor(enactor);
            action.setTarget(target);
            action.setPowerString(args["power"]);
            action.enact(makeActionScope(scope));
        }
      }

      return true;
    }


  }  // namespace command
}  // namespace omush
