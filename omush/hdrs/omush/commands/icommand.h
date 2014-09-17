/**
 * \file icommand.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_ICOMMAND_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_ICOMMAND_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/network/common.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/uuid.h"
#include "omush/scope.h"

namespace omush {
  class ICommand;
  class ICommandDefinition {
   public:
    virtual std::string name() = 0;
    virtual std::unique_ptr<ICommand> factory() = 0;
    virtual std::vector<std::string> patterns() = 0;
  };

  class ICommand {
   public:
    ICommand() {}
    virtual bool execute(std::shared_ptr<CommandScope> scope) = 0;
   private:
  };

  typedef std::shared_ptr<ICommandDefinition> CommandDefinitionPtr;
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_ICOMMAND_H_
