/**
 * \file patterncommandmatcher.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_PATTERNCOMMANDMATCHER_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_PATTERNCOMMANDMATCHER_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/icommandmatcher.h"

namespace omush {
  class PatternCommandMatcher : public ICommandMatcher {
   public:
    PatternCommandMatcher();
    virtual bool
      match(std::string,
            std::vector<std::shared_ptr<ICommandDefinition> > commands,
            std::shared_ptr<ICommandDefinition> &definition) override;
   protected:
    bool _getFirstWordFromString(std::string str,
                                 std::string &word);
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_PATTERNCOMMANDMATCHER_H_
