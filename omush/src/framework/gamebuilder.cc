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

namespace omush {
  GameBuilder::GameBuilder() {
  }

  bool GameBuilder::setupNetwork(IGameInstance* instance) const {
    std::shared_ptr<INetworkManager> ptr(new NetworkManager);

    ptr->addServer(new WebSocketServer());
    instance->network = ptr;

    return true;
  }
}  // namespace omush
