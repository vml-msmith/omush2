/**
 * \file go.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/go.h"

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
#include "omush/actions/actionsystem.h"
#include "omush/actions/actions/go.h"
#include "omush/functions/iexpressionengine.h"

namespace omush {
  namespace command {

    std::string GoDefinition::name() {
      return "GO";
    }

    std::vector<std::string> GoDefinition::getAliasList() {
      std::vector<std::string> alias;
      return alias;
    }

    std::unique_ptr<ICommand> GoDefinition::factory() {
      return std::unique_ptr<ICommand>(new Go);
    }

    std::vector<std::string> GoDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("COMMAND_NAME (?P<name>(.+))");
      return patterns;
    }

    Go::Go() {
    }

    bool Go::execute(std::shared_ptr<CommandScope> scope) {
      GoDefinition def;
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);

      std::string target = "";
      std::map<std::string,std::string> args;
      unpackArgs_(scope, def, args);
      if (args.find("name") == args.end()) {
        // TODO(msmith): Should never get here.
        return false;
      }

      target = args["name"];

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
          actions::ActionSystem system;
          std::shared_ptr<actions::Action> a;
          system.provision<actions::Go>(a);
          std::shared_ptr<actions::Go> go =
            std::dynamic_pointer_cast<actions::Go>(a);

          actions::Go action;
          go->setEnactor(looker);
          go->setTarget(targetObjects->front());
          go->enact(aScope);
        }
      }
      else {
        Notifier::notify(NULL, looker, library::OString("Can't find it"), makeActionScope(scope));
      }

      return true;
    }

  }  // namespace command
}  // namespace omush
