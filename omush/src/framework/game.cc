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


namespace omush {
  Game::Game() : initialized_(false) {
  }

  Game::~Game() {
  }

  bool Game::isInitialized() const {
    return initialized_;
  }

  bool Game::initialize(IGameInstance* instance) {
    instance->game = this;
    instance_ = instance;
    if (!instance->isComplete())
      return false;

    instance_->network->start();
    initialized_ = true;
    return true;
  }

  bool Game::initialize(IGameInstance* instance, IGameBuilder* builder) {
    builder->setupNetwork(instance);

    return initialize(instance);
  }

  bool Game::loop() {
    if (!initialized_)
      return false;

    instance_->network->poll();

    loopNewMessages_();
    loopQueues_();

    if (isRebooting_)
      return false;

    return initialized_;
  }

  void Game::sendNetworkMessageByDescriptor(DescriptorID id,
                                            std::string message) {
    NetworkPacket outPacket = NetworkPacket(message);
    instance_->network->sendMessage(NetworkPacketDescriptorPair(outPacket,
                                                                id));
  }

  void Game::sendNetworkMessage(Connection conn,
                                std::string message) {
    sendNetworkMessageByDescriptor(conn.id, message);
  }

  void Game::shutdown() {
  }

  void Game::loopNewMessages_() {
    NetworkPacketDescriptorPair message;

    while (instance_->network->getNextMessage(&message)) {
      DescriptorID id;
      NetworkPacket packet;
      std::tie(packet, id)  = message;

      Connection conn;
      if (!descriptorIDToConnection_(id, &conn)) {
        newConnection_(id, &conn);
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
      QueueObject object = discardQueue.front();
      discardQueue.pop();

      if (false) {
        instance_->commandQueue->addQueueObject(object);
      }
      else {
        sendNetworkMessageByDescriptor(object.descId, "I don't recognize that command.");
      }
    }

    instance_->commandQueue->loop(instance_, &discardQueue);
  }

  void Game::processIncommingNetworkPacket_(Connection conn,
                                            NetworkPacket packet) {
    QueueObject object;
    object.gameInstance = instance_;
    object.descId = conn.id;
    object.originalString = packet.text;

    descriptorQueue_.addQueueObject(object);
  }

  bool Game::descriptorIDToConnection_(DescriptorID id,
                                       Connection* connection) {
    if (connectedDescriptors_.find(id) == connectedDescriptors_.end()) {
      return false;
    }

    *connection = connectedDescriptors_[id];
    return true;
  }

  bool Game::newConnection_(DescriptorID id,
                            Connection* conn) {
    connectedDescriptors_[id] = Connection(id);
    *conn =  connectedDescriptors_[id];
    sendNetworkMessage(id, "Welcome");
    return true;
  }

  void Game::createRebootFiles_() {
    /*
    boost::filesystem::path dir = "reboot";
    if (!exists(dir)) {
      printf("Create directory\n");
      boost::filesystem::create_directory(dir);
    }

    namespace fs = boost::filesystem;

    boost::filesystem::directory_iterator it(dir), eod;

    while (it!=eod) {
      boost::filesystem::remove(*it);
      it++;
    }

    for (auto& item : connectedDescriptors_) {
      try {
        std::string serializedUUID = boost::lexical_cast<std::string>(item.first);
        sendNetworkMessageByDescriptor(item.first, "REBOOT_ID:" + serializedUUID);
        std::ofstream ofs("reboot/" + serializedUUID);
        boost::archive::text_oarchive oa(ofs);
        oa << item.second;
        instance_->network->poll();
        instance_->network->closeConnection(item.first);
      }
      catch (std::exception &e) {
        printf("Exception\n");
      }
    }*/
  }

  void Game::reboot_() {
    isRebooting_ = true;
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
