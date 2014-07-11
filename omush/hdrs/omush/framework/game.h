/**
 * \file game.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_

#include "omush/framework/igame.h"
#include <map>
#include "omush/network/common.h"

namespace omush {
  class IGameInstance;
  class Game : public IGame {
   public:
    Game();
    virtual ~Game();
    virtual bool isInitialized() const override;
    virtual bool initialize(IGameInstance* instance) override;
    virtual bool initialize(IGameInstance* instance, IGameBuilder* builder);
    virtual bool loop() override;
    virtual void shutdown() override;
    void sendNetworkMessage(DescriptorID id,
                            std::string message);

   private:
    virtual void loopNewMessages_();

    struct Connection {
      DescriptorID id;
      Connection() {}
      Connection(DescriptorID id) : id(id) {}
    };
    typedef std::map<DescriptorID, Connection> DescriptorMap;

    DescriptorMap connectedDescriptors_;
    bool descriptorIDToConnection_(DescriptorID id, Connection* connection);
    bool newConnection_(DescriptorID id,
                        Connection* conn);

    bool initialized_;
    IGameInstance *instance_;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_
