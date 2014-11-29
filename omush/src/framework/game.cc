/**
 * \file game.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/framework/game.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/filesystem.hpp>

#include <sys/types.h>
#include <sys/wait.h>

#include <boost/algorithm/string.hpp>
#include "omush/framework/igameinstance.h"
#include "omush/framework/igamebuilder.h"
#include "omush/network/inetworkmanager.h"
#include "omush/network/common.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "SQLiteCpp/SQLiteCpp.h"
#include "omush/database/databasestorage.h"

namespace omush {
  Game::Game() : initialized_(false), isRebooting_(false), isShutdown_(false) {
  }

  Game::~Game() {
  }

  void Game::close() {
    // Shut down the DB.
    DatabaseStorage dbStorage;
    dbStorage.saveToDatabase("database", instance_->database);

    if (isRebooting_) {
      reboot_();
    }
    else {
      instance_->network->shutdown();
    }
  }

  bool Game::isInitialized() const {
    return initialized_;
  }

  bool Game::initialize(IGameInstance* instance) {
    instance->game = this;
    instance_ = instance;

    if (!instance->isComplete()) {
      return false;
    }

    // isCompelete could theoretically not include a network.
    // Check to make sure it's there.
    if (instance_->network != nullptr)
      instance_->network->start();

    initialized_ = true;
    return true;
  }

  bool Game::initialize(IGameInstance* instance, IGameBuilder* builder) {
    builder->setupNetwork(instance);
    builder->setupDatabase(instance);

    return initialize(instance);
  }

  bool Game::loop() {
    if (!isInitialized()) {
      return false;
    }

    instance_->network->poll();
    loopNewMessages_();
    loopQueues_();

    if (isRebooting_ || isShutdown_) {
      return false;
    }

    return isInitialized();
  }

  void Game::sendNetworkMessageByDescriptor(DescriptorID id,
                                            std::string message) {
    std::cout << "Message: " << message << std::endl;
    NetworkPacket outPacket = NetworkPacket(message);
    instance_->network->sendMessage(NetworkPacketDescriptorPair(outPacket,
                                                                id));
  }

  void Game::sendNetworkMessage(std::shared_ptr<Connection> conn,
                                std::string message) {
    sendNetworkMessageByDescriptor(conn->id, message);
  }

  void Game::shutdown() {
    isShutdown_ = true;
  }

  void Game::reboot() {
    isRebooting_ = true;
  }

  bool Game::getObjectUUIDFromDescriptor(DescriptorID id,
                                         library::uuid &uid) {
    DescriptorToUUIDMap::iterator it = descriptorsToDb_.find(id);

    if (it == descriptorsToDb_.end()) {
      return false;
    }

    uid = it->second;
    return true;
  }

  bool Game::getDescriptorFromObjectUUID(library::uuid uid,
                                         DescriptorID &id) {
    for (auto& it : descriptorsToDb_) {
      if (it.second == uid) {
        id = it.first;
        return true;
      }
    }

    return false;
  }

  void Game::addObjectUUIDForDescriptor(DescriptorID id,
                                        library::uuid uid) {
    if (descriptorsToDb_.find(id) != descriptorsToDb_.end())
      return;

    descriptorsToDb_.insert(std::pair<DescriptorID,
                           library::uuid>(id, uid));
  }

  void Game::removeObjectUUIDForDescriptor(DescriptorID id,
                                           library::uuid uid) {
    if (descriptorsToDb_.find(id) == descriptorsToDb_.end())
      return;

    descriptorsToDb_.erase(id);
  }

  void Game::getDescriptorList(std::vector<DescriptorID> &descriptors) {
    for (auto &it : connectedDescriptors_) {
      descriptors.push_back(it.first);
    }
  }

  void Game::loopNewMessages_() {
    NetworkPacketDescriptorPair message;

    while (instance_->network->getNextMessage(&message)) {
      DescriptorID id;
      NetworkPacket packet;
      std::tie(packet, id)  = message;

      std::shared_ptr<IGame::Connection> conn;

      if (!descriptorIDToConnection_(id, conn)) {
        newConnection_(id, conn);
      } else {
        processIncommingNetworkPacket_(conn, packet);
      }

      return;
    }
  }

  void Game::loopQueues_() {
    QueueObjectQueue discardQueue;
    descriptorQueue_.loop(instance_, &discardQueue);

    while (!discardQueue.empty()) {
      std::shared_ptr<QueueObject> object = discardQueue.front();
      discardQueue.pop();

      if (!library::is_null(object->enactor)) {
        instance_->commandQueue->addQueueObject(object);
      }
      else {
        std::shared_ptr<QueueObject> huh(new QueueObject);
        huh->gameInstance = object->gameInstance;
        huh->descId = object->descId;
        huh->enactor = object->enactor;
        huh->executor = object->enactor;
        huh->caller = object->enactor;
        object->originalString = "WELCOME_SCREEN";
        huh->originalString = "HUH";
        descriptorQueue_.addQueueObject(huh);
        descriptorQueue_.addQueueObject(object);
      }
    }

    if (instance_->commandQueue != nullptr) {
      descriptorQueue_.loop(instance_, &discardQueue);
      instance_->commandQueue->loop(instance_, &discardQueue);

      while (!discardQueue.empty()) {
        std::shared_ptr<QueueObject> object = discardQueue.front();
        discardQueue.pop();

        if (!library::is_null(object->enactor)) {
          object->originalString = "HUH";
          instance_->commandQueue->addQueueObject(object);
        }

      }
    }
  }

  void Game::processIncommingNetworkPacket_(std::shared_ptr<IGame::Connection> conn,
                                            NetworkPacket packet) {
    std::shared_ptr<QueueObject> object(new QueueObject);
    object->gameInstance = instance_;
    object->descId = conn->id;
    object->originalString = packet.text;

    library::uuid uid;
    if (getObjectUUIDFromDescriptor(conn->id, uid)) {
      object->enactor = uid;
      object->caller = uid;
      object->executor = uid;
    }

    descriptorQueue_.addQueueObject(object);
  }

  bool Game::descriptorIDToConnection_(DescriptorID id,
                                       std::shared_ptr<IGame::Connection> &connection) {
    if (connectedDescriptors_.find(id) == connectedDescriptors_.end()) {
      return false;
    }

    connection = connectedDescriptors_[id];
    return true;
  }

  bool Game::newConnection_(DescriptorID id,
                            std::shared_ptr<IGame::Connection>& conn) {
    connectedDescriptors_[id] = std::shared_ptr<Connection>(new Connection(id));
    conn = connectedDescriptors_[id];

    std::shared_ptr<QueueObject> object(new QueueObject);
    object->gameInstance = instance_;
    object->descId = conn->id;
    object->originalString = "WELCOME_SCREEN";

    descriptorQueue_.addQueueObject(object);
    return true;
  }

  void Game::reconnectConnectionById(DescriptorID descId,
                                     std::string uid) {
    try {
      SQLite::Database    db("reboot.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
      // Compile a SQL query, containing one parameter (index 1)
      SQLite::Statement   query(db, "SELECT * FROM reboot WHERE reboot_id = ?");

      // Bind the integer value 6 to the first parameter of the SQL query
      query.bind(1, uid);

      // Loop to execute the query step by step, to get rows of result
      //std::cout << "Try:  " << << std::endl;
      while (query.executeStep()) {
        // Demonstrate how to get some typed column value
        int         id      = query.getColumn(0);
        const char* reboot_uid   = query.getColumn(1);
        const char* db_uid    = query.getColumn(2);

        std::cout << "row: " << id << ", " << reboot_uid << ", " << db_uid << std::endl;
        library::uuid db = boost::lexical_cast<library::uuid>(db_uid);

        std::cout << "Its: " << db << std::endl;
        addObjectUUIDForDescriptor(descId,
                                   db);
      }
      SQLite::Statement   deleteQuery(db, "DELETE FROM reboot WHERE reboot_id = ?");
      deleteQuery.bind(1, uid);
      while (deleteQuery.executeStep()) {}
    }
    catch (std::exception& e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  void Game::createRebootFiles_() {
    printf("Create reboot ID\n");
    // Open a database file
    try {
      SQLite::Database db("reboot.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);

      db.exec("DROP TABLE IF EXISTS reboot");

      // Begin transaction
      SQLite::Transaction transaction(db);

      db.exec("CREATE TABLE reboot (id INTEGER PRIMARY KEY AUTOINCREMENT, reboot_id TEXT, db_id TEXT)");

      for (auto& item : connectedDescriptors_) {
        try {
          std::string serializedUUID = boost::lexical_cast<std::string>(item.first);
          printf("UUID: %s:\n", serializedUUID.c_str());
          DescriptorToUUIDMap::iterator dbit = descriptorsToDb_.find(item.first);
          std::string serializedDBUUID = boost::lexical_cast<std::string>(dbit->second);
          printf("DB UUID: %s\n", serializedDBUUID.c_str());
          sendNetworkMessageByDescriptor(item.first, "REBOOT_ID:" + serializedUUID);

          int nb = db.exec("INSERT INTO reboot VALUES (NULL, \""+serializedUUID+"\", \"" + serializedDBUUID + "\")");


          instance_->network->poll();
          instance_->network->closeConnection(item.first);
        }
        catch (std::exception &e) {
          printf("Exception\n");
        }
      }
      // Commit transaction
      transaction.commit();
    }
    catch (std::exception& e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  void Game::reboot_() {
    isRebooting_ = true;
    createRebootFiles_();
    instance_->network->shutdown();

    pid_t pid = fork(); /* Create a child process */
    switch (pid) {
    case -1: /* Error */
      printf("Uh-Oh! fork() failed.\n");
      exit(1);
    case 0: /* Child process */
      execl("omush", NULL); /* Execute the program */
      printf("Uh-Oh! execl() failed!\n"); /* execl doesn't return unless there's an error */
      exit(1);
    default: /* Parent process */
      printf("Process created with pid %i pid\n",  pid);
      int status;
      printf("Exited");
    }
  }

  template<class Archive>
  void Game::Connection::serialize(Archive & ar, const unsigned int version) {
    rebootId = boost::lexical_cast<std::string>(id);
    ar & rebootId;
  }

}  // namespace omush
