/**
 * \file commandparser.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commandparser.h"
#include "omush/commands/icommand.h"
#include "omush/commands/icommandmatcher.h"

namespace omush {
  CommandParser::CommandParser() {
  }

  bool CommandParser::registerMatcher(std::unique_ptr<ICommandMatcher> cmdMatcher) {
    commandMatchers_.push_back(std::move(cmdMatcher));
    return true;
  }

  bool CommandParser::registerCommand(std::shared_ptr<ICommandDefinition> cmd) {
    commands_.push_back(std::move(cmd));
    return true;
  }

  bool CommandParser::matchCommand(std::string string,
                                   std::shared_ptr<ICommandDefinition> &definition) {
    definition = nullptr;
    for (auto& ptr : commandMatchers_) {
      if (ptr->match(string, commands_, definition)) {
        return true;
      }
    }

    return false;

  }

}  // namespace omush
