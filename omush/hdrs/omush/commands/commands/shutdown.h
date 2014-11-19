/**
 * \file shutdown.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_SHUTDOWN_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_SHUTDOWN_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/command.h"
#include "omush/library/string.h"

namespace omush {
  namespace command {
    /**
     * Definition of the Shutdown command.
     */
    class ShutdownDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
      std::vector<std::string> getAliasList() override;
    };

    /**
     * The @shutdown command.
     */
    class Shutdown : public Command {
     public:
      /**
       * Default constructor.
       */
      Shutdown();

      /**
       * Enact the command.
       */
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_SHUTDOWN_H_
