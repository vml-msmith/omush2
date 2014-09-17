/**
 * \file igame.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_IGAME_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_IGAME_H_

#include "omush/network/common.h"
#include "omush/library/uuid.h"

namespace omush {
  struct IGameInstance;
  class IGameBuilder;

  class IGame {
   public:
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
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_IGAME_H_
