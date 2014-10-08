/**
 * \file huh.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/huh.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/framework/strings.h"
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/library/string.h"
#include "omush/notifier.h"

namespace omush {
  namespace command {

    std::string HuhDefinition::name() {
      return "HUH";
    }

    std::unique_ptr<ICommand> HuhDefinition::factory() {
      return std::unique_ptr<ICommand>(new Huh);
    }

    std::vector<std::string> HuhDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("HUH");
      return patterns;
    }

    Huh::Huh() {
    }

    bool Huh::execute(std::shared_ptr<CommandScope> scope) {
      library::OString lines = Strings::get("COMMAND_NOT_FOUND");

      if (library::is_null(scope->queueObject->executor) &&
          !library::is_null(scope->queueObject->descId)) {
        scope->queueObject->gameInstance->game->sendNetworkMessageByDescriptor(scope->queueObject->descId,
                                                                               lines.plainText());
      }
      else {
        std::shared_ptr<IDatabaseObject> object;
        if (scope->queueObject->gameInstance->database->getObjectByUUID(scope->queueObject->executor,
                                                                        object)) {
          Notifier::notify(NULL, object, lines, makeActionScope(scope));
        }
        else {
          // TODO: Log this.
        }
      }

      return true;
    }

  }  // namespace command
}  // namespace omush
