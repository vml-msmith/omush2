/**
 * \file iserver.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_ISERVER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_ISERVER_H_
#include <stdio.h>
namespace omush {
  class IServer {
   public:
    IServer() {}
    virtual void poll() = 0;
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_NETWORK_ISERVER_H_
