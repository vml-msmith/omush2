/**
 * \file game.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/framework/game.h"
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
    // TODO(msmith): Insert game code to be ran on each loop.
    //               Networking...
    //               Processing...

    instance_->network->poll();

    loopNewMessages_();

    return initialized_;
  }

  void Game::sendNetworkMessage(DescriptorID id,
                                std::string message) {
    NetworkPacket outPacket = NetworkPacket(message);
    instance_->network->sendMessage(NetworkPacketDescriptorPair(outPacket,
                                                                id));
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
      }

      std::string outMessage = packet.text;
      sendNetworkMessage(id, outMessage);

      return;
    }
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

}  // namespace omush
