/**
 * \file set.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/set.h"

#include <memory>
#include <string>
#include <vector>
#include "omush/framework/igame.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/framework/strings.h"
#include "omush/database/databaseobject.h"
#include "omush/database/databasematcher.h"
#include "omush/notifier.h"
#include "omush/actions/actions/setflag.h"


namespace omush {
  namespace command {
    SetDefinition::SetDefinition() {
    }

    std::string SetDefinition::name() {
      return "@SET";
    }

    std::unique_ptr<ICommand> SetDefinition::factory() {
      return std::unique_ptr<ICommand>(new Set);
    }

    std::vector<std::string> SetDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("@set (.+)=(.+)");
      return patterns;
    }

    Set::Set() {
    }

    bool Set::execute(std::shared_ptr<CommandScope> scope) {
      SetDefinition def;
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);

      std::string target = "";
      std::string value = "";

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
            target = what[1];
            if (what.size() > 2) {
              value = what[2];
            }
            break;
          }
        } catch (std::regex_error &e) {
          library::log(std::string(e.what()) +
                       " " +
                       library::parseRegexErrorCode(e.code()));
        }
      }

      std::shared_ptr<IDatabaseObject> looker;
      if (!scope->queueObject->gameInstance->database->getObjectByUUID(scope->queueObject->executor,
                                                                      looker)) {
        // Log.
        return false;
      }


      std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>> targetObjects(new std::vector<std::shared_ptr<IDatabaseObject>>);
      std::shared_ptr<IDatabaseObject> targetObject;
      if (DatabaseMatcher::findTargets(queueObject->gameInstance->database.get(),
                                       looker,
                                       target,
                                       targetObjects)) {
       if (targetObjects->size() > 1) {
          // Too many.
          Notifier::notify(NULL,
                           looker,
                           library::OString(Strings::get("Too many pattern matches")),
                           makeActionScope(scope));
        }
        else {

          actions::SetFlag setAction;
          setAction.setPlayer(looker);
          setAction.setTarget(targetObjects->front());
          setAction.setValue(value);
          setAction.enact(makeActionScope(scope));

        }
      }
      else {
        Notifier::notify(NULL,
                         looker,
                         library::OString("I don't see that here."),
                         makeActionScope(scope));
      }


      return true;
    }

  }  // namespace command
}  // namespace omush
