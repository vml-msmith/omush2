/**
 * \file welcome_screen.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_WELCOME_SCREEN_H_
#define HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_WELCOME_SCREEN_H_

#include "omush/commands/icommand.h"
#include <memory>

namespace omush {
  namespace command {
    class WelcomeScreenDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
    };

    class WelcomeScreen :  public ICommand {
     public:
      WelcomeScreen();
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_WELCOME_SCREEN_H_
