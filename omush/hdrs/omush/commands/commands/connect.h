/**
 * \file connect.h
 *
 * Copyright 2014 Michael Smith
 */


#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_CONNECT_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_CONNECT_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/command.h"

namespace omush {
  namespace command {
    /**
     * Definition of the "Connect" command. Callable from the welcome screen.
     */
    class ConnectDefinition : public ICommandDefinition {
     public:
      /**
       * CONNECT
       */
      virtual std::string name() override;

      /**
       * @return command::Connect
       */
      virtual std::unique_ptr<ICommand> factory() override;

      /**
       * Define the command patterns possible.
       *
       *  - connect <name>
       *  - connect <name> <password>
       *  - connect "<name with space>" <password>
       *
       * @return vector - List of the patterns above.
       */
      virtual std::vector<std::string> patterns() override;
    };

    /**
     * The connect command is used at the Welcome Screen (as a non-logged in
     * user) to login to a player type object.
     */
    class Connect : public Command {
     public:
      /**
       * Default constructor.
       */
      Connect();

      /**
       * Run the command.
       */
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;

     private:
      void sendFailureMessage_(std::shared_ptr<QueueObject> queue);
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_CONNECT_H_
