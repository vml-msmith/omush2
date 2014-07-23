/**
 * \file absolutecommandmatcher.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_ABSOLUTECOMMANDMATCHER_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_ABSOLUTECOMMANDMATCHER_H_

#include "omush/commands/icommandmatcher.h"
#include <memory>

namespace omush {
  class AbsoluteCommandMatcher : public ICommandMatcher {
   public:
    AbsoluteCommandMatcher();
    virtual bool match(std::string, std::vector<std::shared_ptr<ICommandDefinition> > commands,
                       std::shared_ptr<ICommandDefinition> &definition) override;
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_ABSOLUTECOMMANDMATCHER_H_
