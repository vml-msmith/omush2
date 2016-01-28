/**
 * \file isocketserver.h
 *
 * Copyright 2016 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_ISOCKETSERVER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_ISOCKETSERVER_H_

namespace omush {
  class ISocketServer {
  public:
    /**
     * Return the port the server is set to listen on.
     *
     * @return int - Port the server is listening on.
     */
    virtual int getPort() = 0;

    /**
     * Starts the server listening for new connections and messages.
     *
     * TODO(msmith): This should throw an exception of it can't listen. I don't
     * know of any reason it can't listen as of yet. But there will likey be
     * a reason.
     */
    virtual void startListening() = 0;

    /**
     * Execute a poll  and store new messages in an internal buffer.
     *
     * New messages can be retrieved by calling getNetMessage().
     */
    virtual void poll() = 0;

  };
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_NETWORK_ISOCKETSERVER_H_
