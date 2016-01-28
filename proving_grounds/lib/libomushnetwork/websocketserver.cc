/**
 * \file websocketserver.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "websocketserver.h"
#include <assert.h>

namespace omush {

  WebSocketServer::WebSocketServer()
    :port_(0), isListening_(false) {
  }

  int WebSocketServer::getPort() {
    return this->port_;
  }

  void WebSocketServer::startListening(int port) {
    port_ = port;

    assert(this->isListening_ == false);
    this->isListening_ = true;
  }

  void WebSocketServer::poll() {
    assert(this->isListening_);
  }
}
