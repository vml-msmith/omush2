/**
 * \file exitcommandmatcher.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_EXITCOMMANDMATCHER_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_EXITCOMMANDMATCHER_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/icommandmatcher.h"

namespace omush {
  class ExitCommandMatcher : public ICommandMatcher {
   public:
    ExitCommandMatcher();
    virtual bool
      match(std::string,
            std::vector<std::shared_ptr<ICommandDefinition> > commands,
            std::shared_ptr<ICommandDefinition> &definition) override;
   protected:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_EXITCOMMANDMATCHER_H_
