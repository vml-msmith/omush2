/**
 * \file networkmanager.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/network/networkmanager.h"
#include "omush/network/iserver.h"

namespace omush {
  NetworkManager::NetworkManager() {
  }

  bool NetworkManager::addServer(IServer* server) {
    servers_.push_back(std::shared_ptr<IServer>(server));
    return true;
  }

  void NetworkManager::poll() const {
    for (auto& item : servers_) {
      item->poll();
    }
  }

  void NetworkManager::flush() const {
    for (auto& item : servers_) {
      item->flush();
    }
  }

  bool NetworkManager::start() {
    bool success = true;
    for (auto& item : servers_) {
      if (!item->start()) {
        success = false;
      }
    }

    return success;
  }

  bool NetworkManager::shutdown() {
    for (auto& item : servers_) {
      item->shutdown();
    }

    return true;
  }

  bool NetworkManager::sendMessage(NetworkPacketDescriptorPair message) const {
    for (auto& item : servers_) {
      if (item->sendMessage(message)) {
        return true;
      }
    }

    return false;
  }

  bool NetworkManager::closeConnection(DescriptorID id) const {
    for (auto& item : servers_) {
      if (item->closeConnection(id)) {
        return true;
      }
    }

    return false;
  }

  bool NetworkManager::getNextMessage(NetworkPacketDescriptorPair* message) const {
    for (auto& item : servers_) {
      if (item->getNextMessage(message)) {
        return true;
      }
    }

    return false;
  }

}  // namespace omush
