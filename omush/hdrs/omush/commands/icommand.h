/**
 * \file icommand.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_ICOMMAND_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_ICOMMAND_H_

#include <string>

namespace omush {
  class ICommand;
  class ICommandDefinition {
    virtual std::string name() = 0;
    virtual ICommand* factory() = 0;
  };

  class ICommand {
   public:
    ICommand() {}
   private:
  };

  typedef std::shared_ptr<ICommandDefinition> CommandDefinitionPtr;
} // omush

#endif //  OMUSH_HDRS_OMUSH_COMMANDS_ICOMMAND_H_
