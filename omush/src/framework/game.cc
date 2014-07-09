/**
 * \file game.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/framework/game.h"
#include "omush/framework/gameinstance.h"

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
    initialized_ = true;
    return true;
  }

  bool Game::loop() const {
    return initialized_;
  }
}  // namespace omush
