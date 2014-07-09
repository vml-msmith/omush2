/**
 * \file game.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/framework/game.h"
#include "omush/framework/igameinstance.h"
#include "omush/framework/igamebuilder.h"

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

    if (!instance->isComplete())
      return false;

    initialized_ = true;
    return true;
  }

  bool Game::initialize(IGameInstance* instance, IGameBuilder* builder) {
    builder->setupNetwork(instance);
    return initialize(instance);
  }

  bool Game::loop() const {
    // TODO(msmith): Insert game code to be ran on each loop.
    //               Networking...
    //               Processing...

    return initialized_;
  }
}  // namespace omush
