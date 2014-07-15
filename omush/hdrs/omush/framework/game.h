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
#include "omush/network/common.h"
#include "omush/commands/icommandparser.h"

#include <boost/archive/text_oarchive.hpp>

namespace omush {
  class IGameInstance;
  class Game : public IGame {
   protected:
    struct Connection {
      DescriptorID id;
      std::string rebootId;
      friend class boost::serialization::access;
      // When the class Archive corresponds to an output archive, the
      // & operator is defined similar to <<.  Likewise, when the class Archive
      // is a type of input archive the & operator is defined similar to >>.
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version);

      Connection() {}
      Connection(DescriptorID id) : id(id) {}
    };

   public:
    Game();
    virtual ~Game();
    virtual bool isInitialized() const override;
    virtual bool initialize(IGameInstance* instance) override;
    virtual bool initialize(IGameInstance* instance, IGameBuilder* builder);
    virtual bool loop() override;
    virtual void shutdown() override;
    virtual void sendNetworkMessageByDescriptor(DescriptorID id,
                                                std::string message);
    virtual void sendNetworkMessage(Connection connection,
                                    std::string message);
   private:
    virtual void loopNewMessages_();
    virtual void processIncommingNetworkPacket_(Connection conn,
                                                NetworkPacket packet);

    virtual void createRebootFiles_();
    virtual void reboot_();

    typedef std::map<DescriptorID, Connection> DescriptorMap;

    DescriptorMap connectedDescriptors_;
    bool descriptorIDToConnection_(DescriptorID id, Connection* connection);
    bool newConnection_(DescriptorID id,
                        Connection* conn);

    bool initialized_;
    bool isRebooting_;
    IGameInstance *instance_;
    std::shared_ptr<ICommandParser> commandParser_;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_
