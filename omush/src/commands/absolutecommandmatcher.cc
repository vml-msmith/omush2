/**
 * \file absolutecommandmatcher.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/absolutecommandmatcher.h"
#include <boost/algorithm/string.hpp>
#include "omush/commands/icommand.h"
#include <string>
#include <memory>

namespace omush {
  AbsoluteCommandMatcher::AbsoluteCommandMatcher() {
  }

  bool AbsoluteCommandMatcher::match(std::string string,
                                     std::vector<std::shared_ptr<ICommandDefinition> > commands,
                                     std::shared_ptr<ICommandDefinition> &definition) {
return false;
    for (auto& ptr : commands) {
      if (boost::iequals(ptr->name(), string)) {
        definition = ptr;
printf("And it matches absolute?\n");
        return true;
      }
    }
  }
}  // namespace omush
