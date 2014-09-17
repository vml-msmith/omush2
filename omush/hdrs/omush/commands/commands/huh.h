/**
 * \file huh.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_HUH_H_
#define HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_HUH_H_

#include "omush/commands/icommand.h"
#include <memory>

namespace omush {
  namespace command {
    class HuhDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
    };

    class Huh : public ICommand {
     public:
      Huh();
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_HUH_H_
