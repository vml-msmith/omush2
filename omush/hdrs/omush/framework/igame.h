/**
 * \file igame.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_IGAME_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_IGAME_H_

#include "omush/network/common.h"
#include "omush/library/uuid.h"
#include "omush/library/time.h"

namespace omush {
  struct IGameInstance;
  class IGameBuilder;

  class IGame {
   public:
    struct Connection {
     public:
      DescriptorID id;
      std::string rebootId;
      library::time connectTime;
      library::time lastActiveTime;
    };

    IGame() {}
    virtual ~IGame() {}
    virtual bool isInitialized() const = 0;
    virtual bool initialize(IGameInstance* instance) = 0;
    virtual bool initialize(IGameInstance* instance, IGameBuilder* builder) = 0;
    virtual bool loop() = 0;
    virtual void shutdown() = 0;
    virtual void sendNetworkMessageByDescriptor(DescriptorID id,
                                                std::string message) = 0;
    virtual bool getObjectUUIDFromDescriptor(DescriptorID id,
                                             library::uuid &uid) = 0;
    virtual bool getDescriptorFromObjectUUID(library::uuid uid,
                                             DescriptorID &id) = 0;
    virtual void addObjectUUIDForDescriptor(DescriptorID id,
                                            library::uuid uid) = 0;
    virtual void removeObjectUUIDForDescriptor(DescriptorID id,
                                               library::uuid uid) = 0;
    virtual void getDescriptorList(std::vector<DescriptorID> &descriptors) = 0;
    virtual bool descriptorIDToConnection_(DescriptorID id,
                                           std::shared_ptr<IGame::Connection> &connection) = 0;
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_IGAME_H_
