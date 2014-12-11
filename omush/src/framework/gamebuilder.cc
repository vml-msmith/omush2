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
#include "omush/database/databasestorage.h"
#include "omush/database/databaseobject.h"
#include "omush/database/databasefactory.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionplayer.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionroom.h"

#include "omush/functions/functions/add.h"
#include "omush/database/utilities.h"


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
instance->database = dptr;

    // Load the database if possible.
    DatabaseStorage dbStorage;
    if (dbStorage.loadFromDatabase("database", dptr)) {
      // Worked.
    }
    else {

      dptr->flags.addFlag(Flag("Director", 'D'));
      dptr->flags.addFlag(Flag("Admin", 'A'));
      dptr->flags.addFlag(Flag("Hidden", 'h'));
      dptr->flags.addFlag(Flag("No_Walls", 'W'));
      dptr->flags.addFlag(Flag("No_Gossip", 'G'));
      dptr->flags.addFlag(Flag("Haven", 'H'));

      dptr->powers.add(Power("Unlimited Quota",
                             "Privilege to build and create without quota restrictions", false));
      dptr->powers.add(Power("Unlimited Credits",
                             "Privilege to execute actions without credit restrictions", false));
      dptr->powers.add(Power("Teleport Any Object",
                             "Ability to @teleport any object", true));
      dptr->powers.add(Power("Teleport Anywhere",
                             "Abiltiy to @teleport to any location", true));
      dptr->powers.add(Power("Modify",
                             "Ability to modify other people's objects", true));
      dptr->powers.add(Power("Hide From Everyone",
                             "Privilege to hide from everyone", true));

      DatabaseFactory factory;

      std::shared_ptr<DatabaseObject> roomZero;
      factory.buildObject(DatabaseObjectDefinitionRoom::getInstance(),
                          roomZero);
      roomZero->setDbref(instance->database->getNextDbref());
      roomZero->setName("Room Zero");
      roomZero->setAttribute("description",
                             "This is room zero..");
      instance->database->addObject(roomZero);


      std::shared_ptr<DatabaseObject> masterRoom;
      factory.buildObject(DatabaseObjectDefinitionRoom::getInstance(),
                          masterRoom);
      masterRoom->setDbref(instance->database->getNextDbref());
      masterRoom->setName("Master");
      masterRoom->setAttribute("description",
                             "This is the master room");
      instance->database->addObject(masterRoom);

      std::shared_ptr<DatabaseObject> playerOne;
      factory.buildObject(DatabaseObjectDefinitionPlayer::getInstance(),
                          playerOne);
      playerOne->setName("One");
      addPower(instance->database, playerOne, "Unlimited Quota");
      addPower(instance->database, playerOne, "Unlimited Credits");
      addPower(instance->database, playerOne, "Hide From Everyone");
      addPower(instance->database, playerOne, "Modify Any Object", 3);

      // TODO(msmith): Abstract to a databasemove function.
      playerOne->setDbref(instance->database->getNextDbref());
      playerOne->setLocation(roomZero);
      roomZero->addContent(playerOne);
      instance->database->addObject(playerOne);
      instance->database->setRootUser(playerOne);

    }


      dptr->flags.addFlag(Flag("Director", 'D'));
      dptr->flags.addFlag(Flag("Admin", 'A'));
      dptr->flags.addFlag(Flag("Hidden", 'h'));
      dptr->flags.addFlag(Flag("No_Walls", 'W'));
      dptr->flags.addFlag(Flag("No_Gossip", 'G'));
      dptr->flags.addFlag(Flag("Haven", 'H'));

      dptr->powers.add(Power("Unlimited Quota",
                             "Privilege to build and create without quota restrictions", false));
      dptr->powers.add(Power("Unlimited Credits",
                             "Privilege to execute actions without credit restrictions", false));
      dptr->powers.add(Power("Teleport Any Object",
                             "Ability to @teleport any object", true));
      dptr->powers.add(Power("Teleport Anywhere",
                             "Abiltiy to @teleport to any location", true));
      dptr->powers.add(Power("Modify",
                             "Ability to modify other people's objects", true));
      dptr->powers.add(Power("Hide From Everyone",
                             "Privilege to hide from everyone", true));
      dptr->powers.add(Power("Shutdown",
                             "Use the @shutdwon command", true));



    return true;
  }
}  // namespace omush
