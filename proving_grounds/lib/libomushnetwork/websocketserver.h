/**
 * \file websocketserver.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_

#include "isocketserver.h"

namespace omush {
  class WebSocketServer : public ISocketServer {
   public:
    explicit WebSocketServer();

    /**
     * Return the port the server is set to listen on.
     *
     * @return int - Port the server is listening on.
     */
    int getPort() override;

    /**
     * Starts the server listening on port for new connections and messages.
     *
     * @param int port - The port number to listen for new connections on.
     *
     * TODO(msmith): This should throw an exception of it can't listen. I don't
     * know of any reason it can't listen as of yet. But there will likey be
     * a reason.
     */
    void startListening(unsigned int port) override;

    /**
     * Execute a poll  and store new messages in an internal buffer.
     *
     * New messages can be retrieved by calling getNetMessage().
     */
    void poll() override;

   private:
    unsigned int port_;
    bool isListening_;
  };
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_
