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
  bool Command::unpackArgs_(std::shared_ptr<CommandScope> scope,
                            ICommandDefinition& def,
                            std::map<std::string, std::string>& matches) {
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
            std::cout << "Matched " << pat << std::endl;
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

  bool Command::getEnactor_(std::shared_ptr<CommandScope> scope,
                            std::shared_ptr<IDatabaseObject> &enactor) {
    if (!scope->
        queueObject->
        gameInstance->
        database->
        getObjectByUUID(scope->queueObject->executor,
                        enactor)) {
      return false;
    }
    return true;
  }

  void Command::registerStrings_(Strings::ReplaceMap strings) {
    for (auto& item : strings) {
      Strings::addStringIfNotPresent(item.first, item.second);
    }
  }

}  // namespace omush
