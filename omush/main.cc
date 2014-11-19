/**
 * \file main.cc
 *
 * Copyright 2014 Michael Smith
 */

#include <cstdlib>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
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

  double loopSeconds_ = .01;
  double clock_threshhold = CLOCKS_PER_SEC * loopSeconds_;
  clock_t this_time = clock();
  clock_t last_time = this_time;

  printf("Game setup...\n");

  while (game->loop() && !signal.caughtInterupt) {
    this_time = clock();
    if (this_time - last_time < clock_threshhold) {
      boost::this_thread::sleep(boost::posix_time::microseconds(clock_threshhold - (this_time - last_time)));
    }
    last_time = this_time;
  }

  game->close();

  return EXIT_SUCCESS;
}
