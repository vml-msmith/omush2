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
  class ICommandQueue;
  class IDatabase;
  class IExpressionEngine;

  struct IGameInstance {
    IGame* game;
    std::shared_ptr<INetworkManager> network;
    std::shared_ptr<ICommandQueue> commandQueue;
    std::shared_ptr<IDatabase> database;
    std::shared_ptr<IExpressionEngine> expressionEngine;

    IGameInstance() : game(nullptr), network(nullptr) {}

    /**
     * Return true if all of the instances' pointers have been set to a NON null
     * value.
     *
     * Any derived methods on sub-classes must follow this restriction. Parts
     * of the game are very dependent on this. There is no reason to need
     * a test for the existance of one of these pointers every time this object
     * is used.
     *
     * @return true - There are no NULL pointers on the object.
     * @return false - There are NULL pointers on the object, and it's not safe
     *                 to use.
     */
    virtual bool isComplete() const {
      if (network == nullptr ||
          game == nullptr ||
          commandQueue == nullptr ||
          database == nullptr)
        return false;

      return true;
    }
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMEINSTANCE_H_
