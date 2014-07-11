/**
 * \file main.cc
 *
 * Copyright 2014 Michael Smith
 */

#include <cstdlib>
#include "omush/framework/game.h"
#include "omush/framework/gameinstance.h"
#include "omush/framework/gamebuilder.h"
#include "omush/signal/signalhandler.h"

class GameSignalDelegate : public omush::SignalHandlerDelegate {
 public:
  bool caughtInterupt;
  GameSignalDelegate() : caughtInterupt(false) {}
  void handleSignal(int signal) {
    printf("\nCaught SIGINT. Shutting down...\n");
    caughtInterupt = true;
  }
};

int main(int argc, char** argv) {
  using omush::SignalHandler;
  using omush::IGame;
  using omush::Game;
  using omush::GameInstance;
  using omush::GameBuilder;

  GameSignalDelegate signal;
  SignalHandler::setupSignalHandling();
  SignalHandler::registerDelegate(&signal, SIGINT);

  std::unique_ptr<IGame> game(new Game);
  GameInstance instance;

  game->initialize(&instance, new GameBuilder());

  while (game->loop() && !signal.caughtInterupt) {
  }

  game->shutdown();

  return EXIT_SUCCESS;
}
