/**
 * \file quit.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/quit.h"

namespace omush {
  namespace command {
    std::string QuitDefinition::name() {
      return "QUIT";
    }

    ICommand* QuitDefinition::factory() {
      return new Quit();
    }

    Quit::Quit() {
    }

  }  // namespace command
}  // namespace omush
