/**
 * \file connect.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/connect.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/database/databaseobject.h"
#include "omush/database/databasematcher.h"

namespace omush {
  namespace command {

    std::string ConnectDefinition::name() {
      return "CONNECT";
    }

    std::unique_ptr<ICommand> ConnectDefinition::factory() {
      return std::unique_ptr<ICommand>(new Connect);
    }

    std::vector<std::string> ConnectDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("connect ([^[:space:]]+)");
      patterns.push_back("connect \"(.+)\"[[:space:]]+([^[:space:]]+)");
      patterns.push_back("connect ([^[:space:]]+)[[:space:]]([^[:space:]]+)");
      return patterns;
    }

    Connect::Connect() {
    }

    bool Connect::execute(CommandScope scope) {
      ConnectDefinition def;
      std::string userName = "";
      std::string password = "";

      std::vector<std::string> patterns = def.patterns();
      for (auto p : patterns) {
        try {
          std::regex rx(p.c_str(), std::regex::icase);
          std::smatch what;
          if (std::regex_match(scope.originalString, what, rx)) {
            for (size_t i = 0; i < what.size(); ++i) {
              std::ssub_match sub_match = what[i];
              std::string piece = sub_match.str();
              printf("Match %i: %s\n", i, piece.c_str());
            }
            userName = what[1];
            if (what.size() > 2) {
              password = what[2];
            }
            break;
          }
        } catch (std::regex_error &e) {
          library::log(std::string(e.what()) +
                       " " +
                       library::parseRegexErrorCode(e.code()));
        }
      }


      std::shared_ptr<DatabaseObject> object;
      DatabaseMatcher::findPlayer(scope.gameInstance->database.get(),
                                  userName,
                                  object);

      // Find username in the database?
      scope.gameInstance->game->sendNetworkMessageByDescriptor(scope.descId, "Hello " + userName + "!");
      return true;
    }

  }  // namespace command
}  // namespace omush
