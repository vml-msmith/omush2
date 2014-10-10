/**
 * \file look.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/look.h"

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
#include "omush/actions/actions/look.h"
#include "omush/functions/iexpressionengine.h"

namespace omush {
  namespace command {

    std::string LookDefinition::name() {
      return "LOOK";
    }

    std::vector<std::string> LookDefinition::getAliasList() {
      std::vector<std::string> alias;
      alias.push_back("L");
      return alias;
    }

    std::unique_ptr<ICommand> LookDefinition::factory() {
      return std::unique_ptr<ICommand>(new Look);
    }

    std::vector<std::string> LookDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("COMMAND_NAME");
      patterns.push_back("COMMAND_NAME (.+)");
      return patterns;
    }

    Look::Look() {
    }

    bool Look::execute(std::shared_ptr<CommandScope> scope) {
      LookDefinition def;
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);

      std::string target = "";

      std::vector<std::string> patterns = def.patterns();

      std::vector<std::string> names = def.getAliasList();
      names.push_back(def.name());

      for (auto p : patterns) {
        for (auto n : names) {
          try {
            std::string pat = p;
            library::string::replace_all(pat, "COMMAND_NAME", n);
            std::regex rx(pat.c_str(), std::regex::icase);
            std::smatch what;
            if (std::regex_match(queueObject->originalString, what, rx)) {
              for (size_t i = 0; i < what.size(); ++i) {
                std::ssub_match sub_match = what[i];
                std::string piece = sub_match.str();
              }
              target = what[1];
              break;
            }
          } catch (std::regex_error &e) {
            library::log(std::string(e.what()) +
                         " " +
                         library::parseRegexErrorCode(e.code()));
          }
        }
      }

      std::shared_ptr<ActionScope> aScope = makeActionScope(scope);
      library::OString tempTarget = library::OString(target);
      scope->queueObject
        ->gameInstance
        ->expressionEngine
        ->parse(tempTarget, makeFunctionScope(aScope), tempTarget);

      target = tempTarget.plainText();

      std::shared_ptr<IDatabaseObject> looker;

      scope->queueObject->getExecutorObject(looker);
      if (!scope->queueObject->gameInstance->database->getObjectByUUID(scope->queueObject->executor,
                                                                      looker)) {
        // Log.
        return false;
      }

      if (target.length() == 0) {
        target = "here";
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
          // Found one.
          actions::Look lookAction;
          lookAction.setEnactor(looker);
          lookAction.setTarget(targetObjects->front());
          lookAction.enact(aScope);
        }
      }
      else {
        Notifier::notify(NULL, looker, library::OString("Test"), makeActionScope(scope));
      }

      return true;
    }

  }  // namespace command
}  // namespace omush
