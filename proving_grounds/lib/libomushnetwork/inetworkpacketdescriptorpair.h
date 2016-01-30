/**
 * \file inetworkpacketdescriptorpair.h
 *
 * Copyright 2016 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_INETWORKPACKETDESCRIPTORPAIR_H_
#define OMUSH_HDRS_OMUSH_NETWORK_INETWORKPACKETDESCRIPTORPAIR_H_

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
     * Starts the server listening on port for new connections and messages.
     *
     * @param int port - The port number to listen for new connections on.
     *
     * TODO(msmith): This should throw an exception of it can't listen. I don't
     * know of any reason it can't listen as of yet. But there will likey be
     * a reason.
     */
    virtual void startListening(unsigned int port) = 0;

    /**
     * Execute a poll  and store new messages in an internal buffer.
     *
     * New messages can be retrieved by calling getNetMessage().
     */
    virtual void poll() = 0;

    /**
     * Get the next message off the message buffer.
     */
    virtual void getNextMessage() = 0;
    ~ISocketServer() {};
  };
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_NETWORK_INETWORKPACKETDESCRIPTORPAIR_H_
