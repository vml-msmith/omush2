/**
 * \file game.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/framework/game.h"

namespace omush {
  Game::Game() : initialized_(false) {
  }

  Game::~Game() {
  }

  bool Game::isInitialized() const {
    return initialized_;
  }

  bool Game::initialize() {
    initialized_ = true;
    return true;
  }
}  // namespace omush
