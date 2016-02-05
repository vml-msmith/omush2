/**
 * \file websocketserver.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "include/omushnetwork/websocketserver.h"
#include <assert.h>

namespace omush {
  namespace network {
  WebSocketServer::~WebSocketServer() {
  }

  WebSocketServer::WebSocketServer()
    :port_(0), isListening_(false) {
  }

  int WebSocketServer::getPort() {
    return this->port_;
  }

  void WebSocketServer::startListening(unsigned int port) {
    assert(this->isListening_ == false);

    port_ = port;
    this->isListening_ = true;
  }

  void WebSocketServer::poll() {
    assert(this->isListening_);
  }

  bool WebSocketServer::getNextMessage(NetworkPacketDescriptorPair messagePair) {
    return false;
  }
}  // namespace network
}  // namespace omush
