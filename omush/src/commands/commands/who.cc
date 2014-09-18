/**
 * \file who.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/who.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/database/databaseobject.h"
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/notifier.h"

namespace omush {
  namespace command {

    std::string WhoDefinition::name() {
      return "WHO";
    }

    std::unique_ptr<ICommand> WhoDefinition::factory() {
      return std::unique_ptr<ICommand>(new Who);
    }

    std::vector<std::string> WhoDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("who");

      return patterns;
    }

    Who::Who() {
    }

    bool Who::execute(std::shared_ptr<CommandScope> scope) {
      WhoDefinition def;
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);

      std::string params;
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
            params = what[1];
            break;
          }
        } catch (std::regex_error &e) {
          library::log(std::string(e.what()) +
                       " " +
                       library::parseRegexErrorCode(e.code()));
        }
      }

      size_t nameSize = 15;
      size_t flagSize = 8;
      size_t onForSize = 8;
      size_t idleSize = 8;
      size_t classSize = 20;
      size_t empireSize = 6;
      size_t doingSize = 15;

      std::vector<WhoColumn> columns;
      columns.push_back(WhoColumn("Name", nameSize));
      columns.push_back(WhoColumn("Flags", flagSize));
      columns.push_back(WhoColumn("OnFor", onForSize));
      columns.push_back(WhoColumn("Idle", idleSize));
      columns.push_back(WhoColumn("Class/Pos", classSize));
      columns.push_back(WhoColumn("Emp", empireSize));
      columns.push_back(WhoColumn("Doing", doingSize));


      library::OString output = formatColumns(columns);

      std::vector<DescriptorID> descs;
      scope->queueObject->gameInstance->game->getDescriptorList(descs);
      for (auto iter : descs) {
        columns[0].value = "...";
        columns[1].value = "...";
        columns[2].value = "...";
        columns[3].value = "...";
        columns[4].value = "...";
        columns[5].value = "...";
      }


      if (library::is_null(scope->queueObject->executor) &&
          !library::is_null(scope->queueObject->descId)) {
        scope->queueObject->gameInstance->game->sendNetworkMessageByDescriptor(scope->queueObject->descId,
                                                                               output.outString());
      }
      else {
        std::shared_ptr<IDatabaseObject> object;
        if (scope->queueObject->gameInstance->database->getObjectByUUID(scope->queueObject->executor,
                                                                        object)) {
          Notifier::notify(NULL, object, output.outString(), makeActionScope(scope));
        }
        else {
          // TODO: Log this.
        }
      }
      /*
      std::shared_ptr<IDatabaseObject> object;
      if (scope->queueObject->gameInstance->database->getObjectByUUID(scope->queueObject->executor,
                                                                      object)) {

        actions::Who sayAction;
        sayAction.setPlayer(object);
        sayAction.setText(say);
        sayAction.enact(makeActionScope(scope));
      }
      else {
        // TODO: Log this.
        }*/

      return true;
    }

  }  // namespace command
}  // namespace omush
