/**
 * \file command.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/command.h"
#include <memory>
#include "omush/library/string.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"

namespace omush {
  bool Command::_unpackArgs(std::shared_ptr<CommandScope> scope,
                            ICommandDefinition& def,
                            std::map<std::string,std::string>& matches) {
    std::shared_ptr<QueueObject> queueObject(scope->queueObject);
    std::vector<std::string> patterns = def.patterns();
    std::vector<std::string> names = def.getAliasList();
    names.push_back(def.name());
    for (auto p : patterns) {
      for (auto n : names) {
        try {
          std::string pat = p;
          library::string::replace_all(pat, "COMMAND_NAME", n);
          if (library::regex_named_match(queueObject->originalString,
                                         pat.c_str(),
                                         matches)) {
            return true;
          }
        } catch (std::regex_error &e) {
          library::log(std::string(e.what()) +
                       " " +
                       library::parseRegexErrorCode(e.code()));
        }
      }
    }
    return false;
  }

}  // namespace omush
