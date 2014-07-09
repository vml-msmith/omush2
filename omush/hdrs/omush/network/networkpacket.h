/**
 * \file networkpacket.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_NETWORKPACKET_H_
#define OMUSH_HDRS_OMUSH_NETWORK_NETWORKPACKET_H_

#include <string>

namespace omush {
  enum NetworkProtocol {
    NetworkProtocolText,
  };

  struct NetworkPacket {
    std::string text;
    NetworkProtocol protocol;

    NetworkPacket()
      : protocol(NetworkProtocolText), text("") {};

    explicit NetworkPacket(std::string str)
      : text(str), protocol(NetworkProtocolText) {}
  };

} // omush

#endif //  OMUSH_HDRS_OMUSH_NETWORK_NETWORKPACKET_H_
