/**
 * \file patterncommandmatcher.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/patterncommandmatcher.h"
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "omush/commands/icommand.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"

namespace omush {
  PatternCommandMatcher::PatternCommandMatcher() {
  }


  bool PatternCommandMatcher::match(std::string string,
                                    std::vector<std::shared_ptr<ICommandDefinition> > commands,
                                    std::shared_ptr<ICommandDefinition> &definition) {
    for (auto& ptr : commands) {
      std::vector<std::string> patterns = ptr->patterns();
      if (patterns.empty()) {
        continue;
      }

      for (auto p : patterns) {
        try {
          std::regex rx(p.c_str(), std::regex::icase);
          std::cmatch what;
          if (std::regex_match(string.c_str(), what, rx)) {
            definition = ptr;
            return true;
          }
        } catch (std::regex_error &e) {
          library::log(std::string(e.what()) +
                       " " +
                       library::parseRegexErrorCode(e.code()));
        }
      }
    }
  }

  bool PatternCommandMatcher::_getFirstWordFromString(std::string str,
                                                      std::string &word) {
    std::vector<std::string> parts;
    boost::split(parts, str, boost::is_any_of(" "));

    if (parts.size() == 0) {
      word = "";
      return false;
    }

    std::vector<std::string> slashParts;
    boost::split(slashParts, parts[0], boost::is_any_of("/"));

    if (slashParts.size() == 0) {
      word = "";
      return false;
    }

    word = slashParts[0];
    return true;
  }
}  // namespace omush
