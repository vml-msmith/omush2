/**
 * \file icommand.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_ICOMMAND_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_ICOMMAND_H_

#include <memory>
#include <string>
#include "omush/network/common.h"
#include "omush/framework/igameinstance.h"

namespace omush {
  class ICommand;
  class ICommandDefinition {
   public:
    virtual std::string name() = 0;
    virtual std::unique_ptr<ICommand> factory() = 0;
    virtual std::vector<std::string> patterns() = 0;
  };

  struct CommandScope {
    std::string originalString;
    DescriptorID descId;
    IGameInstance *gameInstance;
  };

  class ICommand {
   public:
    ICommand() {}
    virtual bool execute(CommandScope scope) = 0;
   private:
  };

  typedef std::shared_ptr<ICommandDefinition> CommandDefinitionPtr;
} // omush

#endif //  OMUSH_HDRS_OMUSH_COMMANDS_ICOMMAND_H_
