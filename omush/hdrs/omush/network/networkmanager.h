/**
 * \file networkmanager.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_NETWORKMANAGER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_NETWORKMANAGER_H_

#include "omush/network/inetworkmanager.h"
#include <vector>

namespace omush {
  class NetworkManager : public INetworkManager {
   public:
    NetworkManager();
    virtual bool addServer(IServer* server) override;
    virtual void poll() const override;
    void flush() const override;
    bool start();
    bool shutdown();
    bool sendMessage(NetworkPacketDescriptorPair message) const override;
    bool closeConnection(DescriptorID id) const override;
    bool getNextMessage(NetworkPacketDescriptorPair* message) const override;
   protected:
    typedef std::vector<std::shared_ptr<IServer> > ServerList;
    ServerList servers_;
  };
}  // omush network

#endif  // OMUSH_HDRS_OMUSH_NETWORK_NETWORKMANAGER_H_
