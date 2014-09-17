/**
 * \file icommandparser.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_ICOMMANDPARSER_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_ICOMMANDPARSER_H_

#include <memory>
#include <string>

namespace omush {
  class ICommandDefinition;
  class ICommandMatcher;
  class ICommandParser {
   public:
    ICommandParser() {}
    virtual bool
      registerMatcher(std::unique_ptr<ICommandMatcher> cmdMatcher) = 0;
    virtual bool
      registerCommand(std::shared_ptr<ICommandDefinition> cmd) = 0;
    virtual bool
      matchCommand(std::string string,
                   std::shared_ptr<ICommandDefinition> &definition) = 0;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_ICOMMANDPARSER_H_
