/**
 * \file think.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/think.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/strings.h"
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/actions/actions/think.h"
#include <iostream>

namespace omush {
  namespace command {

    std::string ThinkDefinition::name() {
      return "THINK";
    }

    std::vector<std::string> ThinkDefinition::getAliasList() {
      std::vector<std::string> alias;
      alias.push_back("th");
      return alias;
    }

    std::unique_ptr<ICommand> ThinkDefinition::factory() {
      return std::unique_ptr<ICommand>(new Think);
    }

    std::vector<std::string> ThinkDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("COMMAND_NAME (?P<arg1>.+)");
      return patterns;
    }

    Think::Think() {
    }

    bool Think::execute(std::shared_ptr<CommandScope> scope) {
      ThinkDefinition def;
      std::map<std::string,std::string> args;
      _unpackArgs(scope, def, args);

      if (args.find("arg1") == args.end()) {
        return true;
      }
      std::string what = args["arg1"];

      std::shared_ptr<IDatabaseObject> object;
      if (scope->queueObject->gameInstance->database->getObjectByUUID(scope->queueObject->executor,
                                                                      object)) {
        actions::Think action;
        action.setPlayer(object);
        action.setText(library::OString(what));
        action.enact(makeActionScope(scope));
      }
      return true;

    }


  }  // namespace command
}  // namespace omush
