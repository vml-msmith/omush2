/**
 * \file connect.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_CONNECT_H_
#define HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_CONNECT_H_

#include "omush/commands/icommand.h"
#include <memory>

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
      virtual bool execute(CommandScope scope) override;
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_CONNECT_H_
