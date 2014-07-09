/**
 * \file common.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_COMMON_H_
#define OMUSH_HDRS_OMUSH_NETWORK_COMMON_H_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "omush/network/networkpacket.h"

namespace omush {
  typedef boost::uuids::uuid DescriptorID;
  typedef std::tuple<NetworkPacket, DescriptorID> NetworkPacketDescriptorPair;

  inline DescriptorID createNewDescriptorID() {
    return boost::uuids::random_generator()();
  }
} // omush

#endif //  OMUSH_HDRS_OMUSH_NETWORK_COMMON_H_
