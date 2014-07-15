/**
 * \file icommandparser.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_ICOMMANDPARSER_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_ICOMMANDPARSER_H_

#include <memory>

namespace omush {
  class ICommandDefinition;
  class ICommandParser {
   public:
    ICommandParser() {};
    virtual bool registerMatcher() = 0;
    virtual bool registerCommand(std::shared_ptr<ICommandDefinition> cmd) = 0;

   private:
  };
} // omush

#endif //  OMUSH_HDRS_OMUSH_COMMANDS_ICOMMANDPARSER_H_
