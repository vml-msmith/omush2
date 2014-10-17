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
#include "omush/library/string.h"

namespace omush {
  PatternCommandMatcher::PatternCommandMatcher() {
  }


  bool PatternCommandMatcher::match(
      std::string string,
      std::vector<std::shared_ptr<ICommandDefinition> > commands,
      std::shared_ptr<ICommandDefinition> &definition) {
    for (auto& ptr : commands) {
      std::vector<std::string> patterns = ptr->patterns();
      if (patterns.empty()) {
        continue;
      }

      std::vector<std::string> names = ptr->getAliasList();
      names.push_back(ptr->name());

      // TODO(msmith): Cache the variations of alias patterns.
      for (auto p : patterns) {
        for (auto n : names) {
          try {
            std::string pat = p;
            std::map<std::string,std::string> matches;
            library::string::replace_all(pat, "COMMAND_NAME", n);
            if (library::regex_named_match(string,
                                           pat.c_str(),
                                           matches)) {
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
  }

  bool PatternCommandMatcher::_getFirstWordFromString(
      std::string str,
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
