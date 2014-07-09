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
}  // namespace omush
