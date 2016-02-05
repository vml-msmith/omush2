/**
 * \file main.cc
 *
 * Copyright 2014 Michael Smith
 */

#include <cstdlib>
#include <chrono>
#include <thread>
#include "omush/framework/game.h"
#include "omush/framework/gameinstance.h"
#include "omush/framework/gamebuilder.h"
#include "omush/signal/signalhandler.h"

/**
 * Dcoumentation
 */
class GameSignalDelegate : public omush::SignalHandlerDelegate {
 public:
  bool caughtInterupt;

  /**
   * Docs
   */
  GameSignalDelegate() : caughtInterupt(false) {}

  /**
   * Docs
   */
  void handleSignal(int signal) {
    printf("\nCaught SIGINT. Shutting down...\n");
    caughtInterupt = true;
  }
};


/**
 * Simple timer class to run the main loop. This object takes a nanosecond
 * interval as the duration each loop of the server should be. If all the
 * processing of game is completed in less than that microsecond interval,
 * the main thread should sleep for the balance of that time.
 */
class GameTimer {
 public:
  /**
   * Default contstructor.
   *
   * @param t
   *   An integer of the nanosecond duration of each loop.
   */
  explicit GameTimer(signed int t) {
    this->loopNanoSeconds_ = std::chrono::nanoseconds(t);
  }

  /**
   * Start the game timer by setting up the time for the first loop.
   */
  void start() {
    this->thisTime_ = std::chrono::high_resolution_clock::now();
    this->lastTime_ = this->thisTime_;
  }

  /**
   * Sleep the timer for the remainder of the time since the last call of
   * sleep or the call to GameTimer::start().
   */
  void sleep() {
    this->thisTime_ = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds duration = this->thisTime_ - this->lastTime_;
    if (duration < this->loopNanoSeconds_) {
      std::chrono::nanoseconds sleep_time =
        (this->loopNanoSeconds_ - duration);
      std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_time));
    }

    this->lastTime_ = this->thisTime_;
  }

 private:
  typedef std::chrono::high_resolution_clock hrc;
  /**
   * Duration of each loop of hte timer.
   */
  std::chrono::nanoseconds loopNanoSeconds_;

  /**
   * The current time of the loop.
   */
  hrc::time_point thisTime_;

  /**
   * The time of the last loop.
   */
  hrc::time_point lastTime_;
};

/**
 * Main method of the server.
 *
 * Start the game server, setup signal interupts and run the main loop based on
 * a timer.
 */
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
  GameTimer timer(10000000);

  printf("Game setup...\n");

  timer.start();
  while (game->loop() && !signal.caughtInterupt) {
    timer.sleep();
  }

  game->close();

  return EXIT_SUCCESS;
}x
