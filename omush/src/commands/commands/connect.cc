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
#include "omush/actions/actions/connect.h"

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

    bool Connect::execute(std::shared_ptr<CommandScope> scope) {
      ConnectDefinition def;
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);

      std::string userName = "";
      std::string password = "";

      std::vector<std::string> patterns = def.patterns();
      for (auto p : patterns) {
        try {
          std::regex rx(p.c_str(), std::regex::icase);
          std::smatch what;
          if (std::regex_match(queueObject->originalString, what, rx)) {
            for (size_t i = 0; i < what.size(); ++i) {
              std::ssub_match sub_match = what[i];
              std::string piece = sub_match.str();
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

      std::shared_ptr<IDatabaseObject> object;
      if (DatabaseMatcher::findPlayer(queueObject->gameInstance->database.get(),
                                      userName,
                                      object)) {
        queueObject->gameInstance->game->addObjectUUIDForDescriptor(queueObject->descId,
                                                             object->getUuid());
        scope->queueObject->executor = object->getUuid();
        actions::Connect connectAction;
        connectAction.setPlayer(object);
        connectAction.enact(makeActionScope(scope));
      }
      else {
        queueObject->gameInstance->game->sendNetworkMessageByDescriptor(queueObject->descId,
                                                                 "Can't find anyone with that name!");
      }

      return true;
    }

  }  // namespace command
}  // namespace omush
