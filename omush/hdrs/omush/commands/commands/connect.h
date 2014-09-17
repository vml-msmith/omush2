/**
 * \file connect.h
 *
 * Copyright 2014 Michael Smith
 */


#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_CONNECT_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_CONNECT_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/icommand.h"

namespace omush {
  namespace command {
    class ConnectDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
    };

    class Connect : public ICommand {
     public:
      Connect();
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_CONNECT_H_
