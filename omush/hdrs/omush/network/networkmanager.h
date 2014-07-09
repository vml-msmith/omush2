/**
 * \file networkmanager.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_NETWORKMANAGER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_NETWORKMANAGER_H_

#include "omush/network/inetworkmanager.h"

namespace omush {
  class NetworkManager : public INetworkManager {
   public:
    NetworkManager() {}
   private:
  };
}  // omush network

#endif  // OMUSH_HDRS_OMUSH_NETWORK_NETWORKMANAGER_H_
