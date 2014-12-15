/**
 * \file shutdown.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/shutdown.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/strings.h"
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/actions/actions/shutdown.h"
#include "omush/functions/iexpressionengine.h"
#include "omush/database/databaseobject.h"
#include "omush/database/databasematcher.h"

namespace omush {
  namespace command {

    std::string ShutdownDefinition::name() {
      return "@SHUTDOWN";
    }

    std::unique_ptr<ICommand> ShutdownDefinition::factory() {
      return std::unique_ptr<ICommand>(new Shutdown);
    }

    std::vector<std::string> ShutdownDefinition::getAliasList() {
      std::vector<std::string> alias;
      alias.push_back("@SHUTDOWN");
      return alias;
    }

    std::vector<std::string> ShutdownDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("COMMAND_NAME");
      patterns.push_back("COMMAND_NAME(?P<throwaway>/(?P<switch>reboot))");
      return patterns;
    }

    Shutdown::Shutdown() {
    }

    bool Shutdown::execute(std::shared_ptr<CommandScope> scope) {
      ShutdownDefinition def;
      std::map<std::string,std::string> args;
      unpackArgs_(scope, def, args);


      std::shared_ptr<IDatabaseObject> enactor;
      if (!scope->
          queueObject->
          gameInstance->
          database->
          getObjectByUUID(scope->queueObject->executor,
                          enactor)) {
        return true;
      }

      actions::Shutdown action;
      action.setEnactor(enactor);
      action.setReboot(false);
      if (args.find("switch") != args.end()) {
        std::string switchString = args["switch"];
        if (library::string::iequals(switchString, "reboot")) {
          action.setReboot(true);
        }
      }
      action.enact(makeActionScope(scope));
      /*
      std::shared_ptr<IDatabaseObject> target = enactor;
      if (args.find("target") != args.end()) {
        std::shared_ptr<IDatabaseObject> looker;
        scope->queueObject->getExecutorObject(looker);
        library::OString errorString;
        b        std::string targetString = args["target"];
        if (!getTarget_(scope,
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
      }
      else {
        std::string switchString = "add";
        std::string powerString = "";
        int powerLevel = 0;
        explodeInputToPowerStringAndLevel_(args["power"],
                                           powerString,
                                           powerLevel);

        if (args.find("switch") == args.end()) {
          switchString = args["switch"];
        }

        if (library::string::iequals(switchString, "add") ||
            library::string::iequals(switchString, "grant")) {
            actions::PowerGrant action;
            action.setEnactor(enactor);
            action.setTarget(target);
            action.setPowerLevel(powerLevel);
            action.setPowerString(powerString);
            action.enact(makeActionScope(scope));
        }
        else {
            actions::PowerRevoke action;
            action.setEnactor(enactor);
            action.setTarget(target);
            action.setPowerString(powerString);
            action.enact(makeActionScope(scope));
        }
      }
      */
      return true;
    }

  }  // namespace command
}  // namespace omush
