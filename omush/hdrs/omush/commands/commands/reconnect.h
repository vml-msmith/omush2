/**
 * \file reconnect.h
 *
 * Copyright 2014 Michael Smith
 */


#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_RECONNECT_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_RECONNECT_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/command.h"

namespace omush {
  namespace command {
    class ReConnectDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
    };

    class ReConnect : public Command {
     public:
      ReConnect();
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_RECONNECT_H_
