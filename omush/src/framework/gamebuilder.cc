/**
 * \file gamebuilder.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/framework/gamebuilder.h"
#include <memory>
#include "omush/framework/igameinstance.h"
#include "omush/network/networkmanager.h"
#include "omush/network/websocketserver.h"
#include "omush/queue/commandqueue.h"
#include "omush/database/database.h"
#include "omush/database/databaseobject.h"
#include "omush/database/databasefactory.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionplayer.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionroom.h"

namespace omush {
  GameBuilder::GameBuilder() {
  }

  bool GameBuilder::setupNetwork(IGameInstance* instance) const {
    std::shared_ptr<INetworkManager> ptr(new NetworkManager);

    ptr->addServer(new WebSocketServer(1701));
    instance->network = ptr;


    // Setup queues
    std::shared_ptr<ICommandQueue> qptr(new CommandQueue);
    instance->commandQueue = qptr;

    return true;
  }

  bool GameBuilder::setupDatabase(IGameInstance* instance) const {
    std::shared_ptr<IDatabase> dptr(new Database);
    instance->database = dptr;
    DatabaseFactory factory;

    std::shared_ptr<DatabaseObject> roomZero;
    factory.buildObject(DatabaseObjectDefinitionRoom::getInstance(),
                        roomZero);
    roomZero->setName("Room Zero");
    instance->database->addObject(roomZero);

    std::shared_ptr<DatabaseObject> playerOne;
    factory.buildObject(DatabaseObjectDefinitionPlayer::getInstance(),
                        playerOne);
    playerOne->setName("One");

// TODO(msmith): Abstract to a databasemove function.
    playerOne->setLocation(roomZero);
    roomZero->addContent(playerOne);
    instance->database->addObject(playerOne);


    std::shared_ptr<DatabaseObject> playerTwo;
    factory.buildObject(DatabaseObjectDefinitionPlayer::getInstance(),
                        playerTwo);
    playerTwo->setName("Two");

// TODO(msmith): Abstract to a databasemove function.
    playerTwo->setLocation(roomZero);
    roomZero->addContent(playerTwo);
    instance->database->addObject(playerTwo);
    return true;
  }
}  // namespace omush
