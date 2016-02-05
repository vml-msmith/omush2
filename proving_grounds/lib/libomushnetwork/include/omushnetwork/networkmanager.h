/**
 * \file networkmanager.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_NETWORKMANAGER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_NETWORKMANAGER_H_

#include "inetworkmanager.h"
#include <vector>

namespace omush {
namespace network {

class NetworkManager : public INetworkManager {
 public:
  NetworkManager();
  virtual bool addServer(ISocketServer* server) override;
  virtual void poll() const override;
  void flush() const override;
  bool start();
  bool shutdown();
  bool sendMessage(NetworkPacketDescriptorPair message) const override;
  bool closeConnection(DescriptorID id) const override;
  bool getNextMessage(NetworkPacketDescriptorPair* message) const override;
 protected:
  typedef std::vector<std::shared_ptr<ISocketServer> > ServerList;
  ServerList servers_;
};
}  // network
}  // omush

#endif  // OMUSH_HDRS_OMUSH_NETWORK_NETWORKMANAGER_H_
