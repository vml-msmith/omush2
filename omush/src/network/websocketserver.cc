/**
 * \file websocketserver.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/network/websocketserver.h"

namespace omush {
  WebSocketServer::WebSocketServer(int port)
    : port_(port), isRunning_(false) {
  }

  WebSocketServer::~WebSocketServer() {
    shutdown();
  }

  bool WebSocketServer::setupOptions_() {
    server_.set_reuse_addr(true);
    return true;
  }

  bool WebSocketServer::setupHandlers_() {
    server_.set_open_handler(bind(&WebSocketServer::WebSocketDelegate::onOpen,
                                  &delegate_,
                                  ::_1));
    server_.set_close_handler(bind(&WebSocketServer::WebSocketDelegate::onClose,
                                   &delegate_,
                                   ::_1));
    server_.set_message_handler(bind(&WebSocketServer::WebSocketDelegate::onMessage,
                                    &delegate_,
                                     ::_1,
                                     ::_2));
    return true;
  }

  bool WebSocketServer::start() {
    if (isRunning_) {
      return true;
    }

    setupOptions_();
    try {
      server_.init_asio();
      setupHandlers_();
      server_.listen(boost::asio::ip::tcp::v6(), port_);
      server_.start_accept();
    }
    catch (websocketpp::exception &e) {
      // TODO(msmith): These functions MAY throw exepctions, but I'm not
      //               sure what. They should be handled correctly.
      return false;
    }

    isRunning_  = true;
    return true;
  }

  bool WebSocketServer::shutdown() {
    if (!isRunning_) {
      return true;
    }

    printf("Shutting down server.\n");

    server_.stop_listening();
    server_.stop();
    return true;
  }

  void WebSocketServer::poll() {
    if (!isRunning_) {
      return;
    }

    try {
      server_.poll();
    }
    catch (websocketpp::exception &e) {
      // TODO(msmith): I don't know if poll can throw an exception,
      //               but we better be prepared to catch it anyway.
      return;
    }

    getNewConnections_();
    getNewMessages_();
  }

  void WebSocketServer::flush() {
    if (!isRunning_) {
      return;
    }
  }



  bool WebSocketServer::getNextMessage(NetworkPacketDescriptorPair* message) {
    if (!incommingPacketPairs_.empty()) {
      *message = incommingPacketPairs_.front();
      incommingPacketPairs_.pop();
      return true;
    }

    return false;
  }

  bool WebSocketServer::sendMessage(NetworkPacketDescriptorPair message) {
    ConnectionHdl hdl;
    DescriptorID id;
    NetworkPacket packet;

    std::tie(packet, id) = message;
    if (descriptorIDToHdl_(id, &hdl)) {
      try {
        server_.send(hdl,
                     packet.text,
                     websocketpp::frame::opcode::value::TEXT);
      } catch (std::error_code &e) {
        // TODO(msmith): Do some error handling here.
        printf("Error: %s\n", e.message().c_str());
      }
      return true;
    }

    return false;
  }

  bool WebSocketServer::closeConnection(DescriptorID id) {
    ConnectionHdl hdl;
    if (!descriptorIDToHdl_(id, &hdl)) {
      return false;
    }

    server_.close(hdl,
                  websocketpp::close::status::going_away,
                  "Shutdown");
    return true;
  }

  void WebSocketServer::getNewConnections_() {
    ConnectionHdl hdl;

    while (delegate_.getNextNewConnection(&hdl)) {
      // Create a uuid.
      DescriptorID id = createNewDescriptorID();
      addHdlDescriptorMapping(hdl, id);
      NetworkPacket packet = NetworkPacket("");
      incommingPacketPairs_.push(NetworkPacketDescriptorPair(packet,id));
    }
  }

  void WebSocketServer::getNewMessages_() {
    HdlMessageTuple tuple;

    while (delegate_.getNextMessage(&tuple)) {
      DescriptorID id;
      ConnectionHdl hdl;
      WSServer::message_ptr msg;
      std::tie(hdl, msg) = tuple;
      if (!(hdlToDescriptorID_(hdl, &id))) {
        // TODO(msmith): Doesn't work, log this.
        continue;
      }
      NetworkPacket packet = NetworkPacket(msg->get_payload());
      incommingPacketPairs_.push(NetworkPacketDescriptorPair(packet,id));
    }
  }

  void WebSocketServer::addHdlDescriptorMapping(ConnectionHdl hdl,DescriptorID id) {
    hdlToDescriptor_.insert(std::make_pair(hdl,id));
    descriptorToHdl_.insert(std::make_pair(id,hdl));
  }

  bool WebSocketServer::hdlToDescriptorID_(ConnectionHdl hdl, DescriptorID* id) {
    if (hdlToDescriptor_.find(hdl) == hdlToDescriptor_.end()) {
      return false;
    }

    *id = hdlToDescriptor_[hdl];
    return true;
  }

  bool WebSocketServer::descriptorIDToHdl_(DescriptorID id, ConnectionHdl* hdl) {
    if (descriptorToHdl_.find(id) == descriptorToHdl_.end()) {
      return false;
    }

    *hdl = descriptorToHdl_[id];
    return true;
  }

  void WebSocketServer::WebSocketDelegate::onMessage(ConnectionHdl hdl,
                                                     WSServer::message_ptr msg) {
    HdlMessageTuple tuple(hdl,msg);
    messages_.push(tuple);
  };

  void WebSocketServer::WebSocketDelegate::onOpen(ConnectionHdl hdl) {
    newConnections_.push(hdl);
    // TODO(msmith): Add a new message? I think that's how we'll notify
    //               the game we have a new item.
  };

  void WebSocketServer::WebSocketDelegate::onClose(ConnectionHdl hdl) {
  };

  bool WebSocketServer::WebSocketDelegate::getNextNewConnection(ConnectionHdl *hdl) {
    if (!newConnections_.empty()) {
      ConnectionHdl h = newConnections_.front();
      *hdl = h;
      newConnections_.pop();
      return true;
    }

    return false;
  }

  bool WebSocketServer::WebSocketDelegate::getNextMessage(HdlMessageTuple *tuple) {
    if (!messages_.empty()) {
      HdlMessageTuple t = messages_.front();
      *tuple = t;
      messages_.pop();
      return true;
    }

    return false;
  }

  bool WebSocketServer::WebSocketDelegate::getNextClosedConnection(ConnectionHdl *hdl) {
    return false;
  }


}  // namespace omush
