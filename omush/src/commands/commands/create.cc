/**
 * \file create.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/create.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/strings.h"
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/actions/actions/create.h"
#include "omush/functions/iexpressionengine.h"
#include "omush/database/databaseobject.h"
#include "omush/database/databasematcher.h"

namespace omush {
  namespace command {

    std::string CreateDefinition::name() {
      return "@CREATE";
    }

    std::unique_ptr<ICommand> CreateDefinition::factory() {
      return std::unique_ptr<ICommand>(new Create);
    }

    std::vector<std::string> CreateDefinition::getAliasList() {
      std::vector<std::string> alias;

      return alias;
    }

    std::vector<std::string> CreateDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("COMMAND_NAME(?P<throwaway> (?P<name>.+))?");
      return patterns;
    }

    Create::Create() {
    }

    bool Create::execute(std::shared_ptr<CommandScope> scope) {
      CreateDefinition def;
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

      if (args.find("name") == args.end()) {
        // TODO(msmith): Should never get here.
        return false;
      }


      actions::Create action;
      action.setEnactor(enactor);
      action.setName(args["name"]);
      action.enact(makeActionScope(scope));

      return true;
    }


  }  // namespace command
}  // namespace omush
