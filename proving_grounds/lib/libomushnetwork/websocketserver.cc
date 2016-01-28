/**
 * \file websocketserver.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "websocketserver.h"
#include <assert.h>

namespace omush {

  WebSocketServer::WebSocketServer(int port)
    :port_(port) {
  }

  int WebSocketServer::getPort() {
    return this->port_;
  }

  void WebSocketServer::startListening() {
  }

  void WebSocketServer::poll() {
    assert(false);
  }
}
