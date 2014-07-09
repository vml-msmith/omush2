/**
 * \file iserver.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_ISERVER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_ISERVER_H_

#include "omush/network/common.h"

namespace omush {
  class IServer {
   public:
    IServer() {}
    virtual void poll() = 0;
    virtual void flush() = 0;
    virtual bool shutdown() = 0;
    virtual bool start() = 0;
    virtual bool getNextMessage(NetworkPacketDescriptorPair* message) = 0;
    virtual bool sendMessage(NetworkPacketDescriptorPair message) = 0;
    virtual bool closeConnection(DescriptorID id) = 0;
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_NETWORK_ISERVER_H_
