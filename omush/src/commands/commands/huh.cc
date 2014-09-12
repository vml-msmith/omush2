/**
 * \file huh.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/huh.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"

namespace omush {
  namespace command {

    std::string HuhDefinition::name() {
      return "HUH";
    }

    std::unique_ptr<ICommand> HuhDefinition::factory() {
      return std::unique_ptr<ICommand>(new Huh);
    }

    std::vector<std::string> HuhDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("HUH");
      return patterns;
    }

    Huh::Huh() {
    }

    bool Huh::execute(CommandScope scope) {

      std::string lines = "I don't recognize that command.";

      scope.gameInstance->game->sendNetworkMessageByDescriptor(scope.descId, lines);
      return true;
    }

  }  // namespace command
}  // namespace omush
