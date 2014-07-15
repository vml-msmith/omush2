/**
 * \file commandparser.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commandparser.h"

namespace omush {
  CommandParser::CommandParser() {
  }

  bool CommandParser::registerMatcher() {
    return true;
  }

  bool CommandParser::registerCommand(std::shared_ptr<ICommandDefinition> cmd) {
    return true;
  }

}  // namespace omush
