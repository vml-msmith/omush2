/**
 * \file websocketserver.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_

#include "isocketserver.h"

namespace omush {
  class WebSocketServer : public ISocketServer {
   public:
    explicit WebSocketServer();

    int getPort() override;
    void startListening(unsigned int port) override;
    void poll() override;
    bool getNextMessage(NetworkPacketDescriptorPair messagePair) override;

   private:
    unsigned int port_;
    bool isListening_;
  };
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_
