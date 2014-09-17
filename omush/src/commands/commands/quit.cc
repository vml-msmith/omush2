/**
 * \file quit.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/quit.h"
#include "omush/framework/igame.h"

namespace omush {
  namespace command {
    std::string QuitDefinition::name() {
      return "QUIT";
    }

    std::unique_ptr<ICommand> QuitDefinition::factory() {
      return std::unique_ptr<ICommand>(new Quit);
    }

    std::vector<std::string> QuitDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("QUIT");
      return patterns;
    }

    Quit::Quit() {
    }

    bool Quit::execute(std::shared_ptr<CommandScope> scope) {
      scope->queueObject->gameInstance->game->sendNetworkMessageByDescriptor(scope->queueObject->descId, "Bye bye");
      return true;
    }

  }  // namespace command
}  // namespace omush
