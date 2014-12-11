/**
 * \file go.h
 *
 * Copyright 2014 Michael Smith
 */


#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_GO_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_GO_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/command.h"

namespace omush {
  namespace command {
    class GoDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
      virtual std::vector<std::string> getAliasList() override;
    };

    class Go : public Command {
     public:
      Go();
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_Go_H_
