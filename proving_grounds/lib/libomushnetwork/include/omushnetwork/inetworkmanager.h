/**
 * \file inetworkmanager.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_INETWORKMANAGER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_INETWORKMANAGER_H_

#include "common.h"

namespace omush {
namespace network {

class ISocketServer;

class INetworkManager {
 public:
  INetworkManager() {}
  virtual bool addServer(ISocketServer* server) = 0;
  virtual void poll() const = 0;
  virtual void flush() const = 0;
  virtual bool start() = 0;
  virtual bool shutdown() = 0;
  virtual bool sendMessage(NetworkPacketDescriptorPair message) const = 0;
  virtual bool closeConnection(DescriptorID id) const = 0;
  virtual bool getNextMessage(NetworkPacketDescriptorPair* message) const { return true; }
 private:
};
}  // omush network
}  // omush omush

#endif  // OMUSH_HDRS_OMUSH_NETWORK_INETWORKMANAGER_H_
