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
#include "omush/functions/expressionengine.h"
#include "omush/database/database.h"
#include "omush/database/databaseobject.h"
#include "omush/database/databasefactory.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionplayer.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionroom.h"

#include "omush/functions/functions/add.h"

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


    // Setup Expression Engine.
    std::shared_ptr<IExpressionEngine> eptr(new ExpressionEngine);
    eptr->registerFunction(std::shared_ptr<IFunctionDefinition>(new functions::AddDefinition));
    instance->expressionEngine = eptr;
    return true;
  }

  bool GameBuilder::setupDatabase(IGameInstance* instance) const {
    std::shared_ptr<IDatabase> dptr(new Database);

    dptr->flags.addFlag(Flag("Director", 'D'));
    dptr->flags.addFlag(Flag("Admin", 'A'));
    dptr->flags.addFlag(Flag("Hidden", 'h'));
    dptr->flags.addFlag(Flag("No_Walls", 'W'));
    dptr->flags.addFlag(Flag("No_Gossip", 'G'));
    dptr->flags.addFlag(Flag("Haven", 'H'));

    instance->database = dptr;
    DatabaseFactory factory;

    std::shared_ptr<DatabaseObject> roomZero;
    factory.buildObject(DatabaseObjectDefinitionRoom::getInstance(),
                        roomZero);
    roomZero->setName("Room Zero");
    roomZero->setAttribute("description",
                           "This is the global room. Hah%R%n%R%B--.");
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
