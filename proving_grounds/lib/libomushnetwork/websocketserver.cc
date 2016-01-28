/**
 * \file websocketserver.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "websocketserver.h"
#include <assert.h>

namespace omush {

  WebSocketServer::WebSocketServer(int port)
    :port_(port), isListening_(false) {
  }

  int WebSocketServer::getPort() {
    return this->port_;
  }

  void WebSocketServer::startListening() {
    this->isListening_ = true;
  }

  void WebSocketServer::poll() {
    assert(this->isListening_);
  }
}
