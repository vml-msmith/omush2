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
#include "omush/framework/strings.h"
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
      patterns.push_back("COMMAND_NAME (?P<name>[^[:space:]]+)");
      patterns.push_back("COMMAND_NAME \"(?P<name>[^\"]+)\"[[:space:]]+([^[:space:]]+)");
      patterns.push_back("COMMAND_NAME (?P<name>[^[:space:]]+)[[:space:]]([^[:space:]]+)");
      return patterns;
    }

    Connect::Connect() {
      static bool hasAddedStrings = false;

      if (hasAddedStrings == false) {
        Strings::ReplaceMap items;
        items["COMMAND_CONNECT__CANT_FIND_PLAYER"] =
          "Can't find anyone with that name.";
       registerStrings_(items);
      }
    }

    bool Connect::execute(std::shared_ptr<CommandScope> scope) {
      ConnectDefinition def;
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);
      std::map<std::string, std::string> args;
      unpackArgs_(scope, def, args);

      std::string userName = args["name"];
      std::string password = "";

      if (args.find("password") != args.end()) {
        password = args["password"];
      }

      std::shared_ptr<IDatabaseObject> object;
      if (DatabaseMatcher::findPlayer(queueObject->gameInstance->database.get(),
                                      userName,
                                      object)) {

        // TOOD(msmith): Compare passwords. First, we need to store passwords.
        queueObject->
          gameInstance->
          game->
          addObjectUUIDForDescriptor(queueObject->descId,
                                     object->getUuid());

        scope->queueObject->executor = object->getUuid();

        actions::Connect connectAction;
        connectAction.setPlayer(object);
        connectAction.enact(makeActionScope(scope));

      } else {
        sendFailureMessage_(queueObject);
        return true;
      }

      return true;
    }

    void Connect::sendFailureMessage_(std::shared_ptr<QueueObject> queue) {
      std::string message =
        Strings::get("COMMAND_CONNECT__CANT_FIND_PLAYER").outString();
      queue->
        gameInstance->
        game->
        sendNetworkMessageByDescriptor(queue->descId,
                                       message);
    }

  }  // namespace command
}  // namespace omush
