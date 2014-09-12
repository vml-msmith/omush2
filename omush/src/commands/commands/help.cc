/**
 * \file help.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/help.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/help/help.h"

namespace omush {
  namespace command {

    std::string HelpDefinition::name() {
      return "HELP";
    }

    std::unique_ptr<ICommand> HelpDefinition::factory() {
      return std::unique_ptr<ICommand>(new Help);
    }

    std::vector<std::string> HelpDefinition::patterns() {
      std::vector<std::string> patterns;
      //      patterns.push_back("help[[:space:]]");
      patterns.push_back("help[[:space:]]?(.+)?");
      return patterns;
    }

    Help::Help() {
    }

    bool Help::execute(CommandScope scope) {
      HelpDefinition def;
      std::string term = "";

      std::vector<std::string> patterns = def.patterns();
      for (auto p : patterns) {
        try {
          std::regex rx(p.c_str(), std::regex::icase);
          std::smatch what;
          if (std::regex_match(scope.originalString, what, rx)) {
            for (size_t i = 0; i < what.size(); ++i) {
              std::ssub_match sub_match = what[i];
              std::string piece = sub_match.str();
            }
            term = what[1];
            break;
          }
        } catch (std::regex_error &e) {
          library::log(std::string(e.what()) +
                       " " +
                       library::parseRegexErrorCode(e.code()));
        }
      }

      std::shared_ptr<HelpEntry> entry;
      if (MyHelp::startInstance("general")->getHelpByIndex(term, entry)) {
        std::string output = entry->index + "\n" + entry->details;
        scope.gameInstance->game->sendNetworkMessageByDescriptor(scope.descId, output);
      }
      else {
        scope.gameInstance->game->sendNetworkMessageByDescriptor(scope.descId, "Unable to find help on '" + term + "'.");
      }
      return true;
    }

  }  // namespace command
}  // namespace omush
