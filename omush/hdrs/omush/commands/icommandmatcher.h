/**
 * \file icommandmatcher.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_ICOMMANDMATCHER_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_ICOMMANDMATCHER_H_

#include <vector>
#include <string>
#include <memory>

namespace omush {
  class ICommandDefinition;
  class ICommandMatcher {
   public:
    ICommandMatcher() {}
    virtual bool match(std::string, std::vector<std::shared_ptr<ICommandDefinition> > commands,
                       std::shared_ptr<ICommandDefinition> &definition) = 0;
   private:
  };
} // omush

#endif //  OMUSH_HDRS_OMUSH_COMMANDS_ICOMMANDMATCHER_H_
