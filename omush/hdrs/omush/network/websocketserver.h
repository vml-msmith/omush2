/**
 * \file websocketserver.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_
#define OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_

#include <queue>
#include <map>
#include "omush/network/iserver.h"
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

namespace omush {
  class WebSocketServer : public IServer {
   public:
    explicit WebSocketServer(int port);
    ~WebSocketServer();
    void poll() override;
    void flush() override;
    bool shutdown()  override;
    bool start() override;
    bool getNextMessage(NetworkPacketDescriptorPair* message)  override;
    bool sendMessage(NetworkPacketDescriptorPair message)  override;
    bool closeConnection(DescriptorID id) override;

   private:
    typedef websocketpp::server<websocketpp::config::asio> WSServer;
    typedef websocketpp::connection_hdl ConnectionHdl;
    typedef std::map<ConnectionHdl,
      DescriptorID,
      std::owner_less<ConnectionHdl> > HdlDescriptorIDMap;
    typedef std::map<DescriptorID,
      ConnectionHdl > DescriptorIDHdlMap;
    typedef std::tuple<ConnectionHdl, WSServer::message_ptr> HdlMessageTuple;

    class WebSocketDelegate {
     public:
      WebSocketDelegate() { }
      ~WebSocketDelegate() {  }

      void onMessage(ConnectionHdl hdl,
                     WSServer::message_ptr msg);
      void onOpen(ConnectionHdl hdl);
      void onClose(ConnectionHdl hdl);

      bool getNextNewConnection(ConnectionHdl *hdl);
      bool getNextClosedConnection(ConnectionHdl *hdl);
      bool getNextMessage(HdlMessageTuple *tuple);

     private:
      std::queue<ConnectionHdl> newConnections_;
      std::queue<HdlMessageTuple> messages_;
    };
    bool setupOptions_();
    bool setupHandlers_();
    void getNewConnections_();
    void getNewMessages_();
    void addHdlDescriptorMapping(ConnectionHdl hdl,DescriptorID id);
    bool hdlToDescriptorID_(ConnectionHdl hdl, DescriptorID* id);
    bool descriptorIDToHdl_(DescriptorID , ConnectionHdl* hdl);


    WSServer server_;
    WebSocketDelegate delegate_;
    bool isRunning_;
    int port_;
    HdlDescriptorIDMap hdlToDescriptor_;
    DescriptorIDHdlMap descriptorToHdl_;
    std::queue<NetworkPacketDescriptorPair> incommingPacketPairs_;
  };
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_NETWORK_WEBSOCKETSERVER_H_
