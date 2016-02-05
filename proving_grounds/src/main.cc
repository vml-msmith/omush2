/**
 * \file main.cc
 */
#include "framework/timer.h"
#include "signal/signalhandler.h"
#include "yaml-cpp/yaml.h"
#include <iostream>

/**
 * Dcoumentation
 */
class GameSignalDelegate : public omush::signal::SignalHandlerDelegate {
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

int main(int argc, char** argv) {
  using omush::signal::SignalHandler;

  GameSignalDelegate signal;
  SignalHandler::setupSignalHandling();
  SignalHandler::registerDelegate(&signal, SIGINT);


  return EXIT_SUCCESS;
}
