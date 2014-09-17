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
    playerOne->setLocation(roomZero);
    instance->database->addObject(playerOne);
    return true;
  }
}  // namespace omush
