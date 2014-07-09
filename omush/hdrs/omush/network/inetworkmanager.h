/**
 * \file inetworkmanager.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_INETWORKMANAGER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_INETWORKMANAGER_H_

namespace omush {
  class IServer;
  class INetworkManager {
   public:
    INetworkManager() {}
    virtual bool addServer(IServer* server) = 0;
    virtual void poll() const = 0;
   private:
  };
}  // omush network

#endif  // OMUSH_HDRS_OMUSH_NETWORK_INETWORKMANAGER_H_
