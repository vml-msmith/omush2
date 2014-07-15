/**
 * \file commandparser.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDPARSER_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDPARSER_H_

#include "omush/commands/icommandparser.h"

namespace omush {
  class CommandParser : public ICommandParser {
   public:
    CommandParser();
    virtual bool registerMatcher();
    virtual bool registerCommand(std::shared_ptr<ICommandDefinition> cmd);
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDPARSER_H_
