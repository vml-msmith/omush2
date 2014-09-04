/**
 * \file help.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/help.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"

namespace omush {
  namespace command {

    std::string HelpDefinition::name() {
      return "HELP";
    }

    std::unique_ptr<ICommand> HelpDefinition::factory() {
      return std::unique_ptr<ICommand>(new Help);
    }

    std::vector<std::string> HelpDefinition::patterns() {
      std::vector<std::string> patterns;
      //      patterns.push_back("help[[:space:]]");
      patterns.push_back("help[[:space:]]?(.+)?");
      return patterns;
    }

    Help::Help() {
    }

    bool Help::execute(CommandScope scope) {
      HelpDefinition def;

      scope.gameInstance->game->sendNetworkMessageByDescriptor(scope.descId, "Show help.");
      return true;
    }

  }  // namespace command
}  // namespace omush
