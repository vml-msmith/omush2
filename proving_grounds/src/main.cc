/**
 * \file main.cc
 */
#include "framework/timer.h"
#include "signal/signalhandler.h"

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


  while (!signal.caughtInterupt) {
    printf("Print\n");
  }
  return EXIT_SUCCESS;
}
