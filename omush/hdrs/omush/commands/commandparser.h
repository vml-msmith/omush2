/**
 * \file commandparser.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDPARSER_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDPARSER_H_

#include "omush/commands/icommandparser.h"
#include "omush/commands/icommandmatcher.h"
#include <vector>

namespace omush {
  class CommandParser : public ICommandParser {
   public:
    CommandParser();
    virtual bool registerMatcher(std::unique_ptr<ICommandMatcher> cmdMatcher);
    virtual bool registerCommand(std::shared_ptr<ICommandDefinition> cmd);
    virtual bool matchCommand(std::string string, std::shared_ptr<ICommandDefinition> &definition) override;

   private:
    typedef std::vector<std::shared_ptr<ICommandDefinition> > CommandDefinitionVector;
    typedef std::vector<std::unique_ptr<ICommandMatcher> > CommandMatcherVector;

    CommandDefinitionVector commands_;
    CommandMatcherVector commandMatchers_;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDPARSER_H_
