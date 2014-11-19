/**
 * \file game.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_

#include "omush/framework/igame.h"
#include <map>
#include <string>
#include <vector>
#include "omush/network/common.h"
#include "omush/queue/descriptorcommandqueue.h"
#include "omush/library/uuid.h"
#include "omush/library/time.h"

// TODO: Why are these here?
#include <boost/archive/text_oarchive.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

namespace omush {
    using namespace boost::gregorian;
  class IGameInstance;
  class Game : public IGame {
   public:
    struct Connection :  IGame::Connection {

      friend class boost::serialization::access;
      // When the class Archive corresponds to an output archive, the
      // & operator is defined similar to <<.  Likewise, when the class Archive
      // is a type of input archive the & operator is defined similar to >>.
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version);

      Connection() {
        connectTime = library::currentTime();
        lastActiveTime = connectTime;
        boost::posix_time::ptime time_t_epoch(date(1970,1,1));
        boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
        boost::posix_time::time_duration diff = connectTime - time_t_epoch;
      }
      Connection(DescriptorID id) {
        this->id = id;
        connectTime = library::currentTime();
        lastActiveTime = connectTime;
      }

      Connection( const Connection& other ) {
        id= other.id;
        rebootId = other.rebootId;
        connectTime = other.connectTime;
        lastActiveTime = other.lastActiveTime;
      }
    };

    Game();
    virtual ~Game();
    virtual void close() override;
    virtual bool isInitialized() const override;
    virtual bool initialize(IGameInstance* instance) override;
    virtual bool initialize(IGameInstance* instance, IGameBuilder* builder);
    virtual bool loop() override;
    virtual void shutdown() override;
    virtual void reboot() override;
    virtual void sendNetworkMessageByDescriptor(DescriptorID id,
                                                std::string message) override;
    virtual void sendNetworkMessage(std::shared_ptr<Connection> connection,
                                    std::string message);
    virtual bool getObjectUUIDFromDescriptor(library::uuid uid,
                                             DescriptorID &id) override;
    virtual bool getDescriptorFromObjectUUID(library::uuid uid,
                                             DescriptorID &id) override;
    virtual void addObjectUUIDForDescriptor(DescriptorID id,
                                            library::uuid uid) override;
    virtual void removeObjectUUIDForDescriptor(DescriptorID id,
                                               library::uuid uid) override;
    virtual void getDescriptorList(std::vector<DescriptorID> &descriptors)
      override;
    virtual bool descriptorIDToConnection_(
        DescriptorID id,
        std::shared_ptr<IGame::Connection> &connection);
   private:
    virtual void loopNewMessages_();
    virtual void loopQueues_();
    virtual void processIncommingNetworkPacket_(std::shared_ptr<IGame::Connection> conn,
                                                NetworkPacket packet);

    virtual void createRebootFiles_();
    virtual void reboot_();

    typedef std::map<DescriptorID, std::shared_ptr<Connection>> DescriptorMap;
    typedef std::map<DescriptorID, library::uuid> DescriptorToUUIDMap;

    DescriptorMap connectedDescriptors_;
    DescriptorToUUIDMap descriptorsToDb_;

    bool newConnection_(DescriptorID id,
                        std::shared_ptr<IGame::Connection> &conn);

    bool initialized_;
    bool isRebooting_;
    bool isShutdown_;
    IGameInstance *instance_;
    DescriptorCommandQueue descriptorQueue_;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_
