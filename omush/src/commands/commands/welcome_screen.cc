/**
 * \file welcome_screen.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/welcome_screen.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"

namespace omush {
  namespace command {

    std::string WelcomeScreenDefinition::name() {
      return "WELCOME_SCREEN";
    }

    std::unique_ptr<ICommand> WelcomeScreenDefinition::factory() {
      return std::unique_ptr<ICommand>(new WelcomeScreen);
    }

    std::vector<std::string> WelcomeScreenDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("WELCOME_SCREEN");
      return patterns;
    }

    WelcomeScreen::WelcomeScreen() {
    }

    bool WelcomeScreen::execute(std::shared_ptr<CommandScope> scope) {

      std::string lines = "";
      lines += "----------------------------------------------------------------------------\n";
      lines += "                    Welcome!\n";
      lines += "----------------------------------------------------------------------------\n";
      lines += "  CONNECT <name> <password>...............Connect to a pre-existing account.\n";
      lines += "  HELP..............................................Display the help system.\n";
      lines += "  QUIT.............................................Disconnect from the game.\n";

      scope->queueObject->gameInstance->game->sendNetworkMessageByDescriptor(scope->queueObject->descId, lines);
      return true;
    }

  }  // namespace command
}  // namespace omush
