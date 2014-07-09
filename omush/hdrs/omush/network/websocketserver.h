/**
 * \file websocketserver.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_

#include "omush/network/iserver.h"

namespace omush {
  class WebSocketServer : public IServer {
   public:
    WebSocketServer() {}
    virtual void poll() override {}
   private:
  };
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_
