/**
 * \file igameinstance.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMEINSTANCE_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMEINSTANCE_H_

#include <memory>

namespace omush {
  class IGame;
  class INetworkManager;
  struct IGameInstance {
    IGame* game;
    std::shared_ptr<INetworkManager> network;
    IGameInstance() : game(nullptr), network(nullptr) {}
    virtual bool isComplete() const {
      if (network == nullptr ||
          game == nullptr)
        return false;

      return true;
    }
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMEINSTANCE_H_
