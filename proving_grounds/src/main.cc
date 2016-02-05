/**
 * \file main.cc
 *
 * Copyright 2014 Michael Smith
 */
#include <signal.h>
#include "framework/timer.h"
#include "signal/signalhandler.h"
#include "yaml-cpp/yaml.h"
#include "omushnetwork/networkmanager.h"
#include "omushnetwork/websocketserver.h"

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

// Setup the network.
std::shared_ptr<omush::network::INetworkManager> ptr(new omush::network::NetworkManager);
ptr->addServer(new omush::network::WebSocketServer());


  return EXIT_SUCCESS;
}
