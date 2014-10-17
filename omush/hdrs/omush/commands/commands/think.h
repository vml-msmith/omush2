/**
 * \file think.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_THINK_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_THINK_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/icommand.h"
#include "omush/commands/command.h"


namespace omush {
  namespace command {
    class ThinkDefinition : public ICommandDefinition {
    public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
      std::vector<std::string> getAliasList() override;
    };

    class Think : public Command {
     public:
      Think();
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_THINK_H_
