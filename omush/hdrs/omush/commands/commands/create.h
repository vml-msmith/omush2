/**
 * \file create.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_CREATE_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_CREATE_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/command.h"
#include "omush/library/string.h"

namespace omush {
  namespace command {
    /**
     * Definition of the Create command.
     */
    class CreateDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
      std::vector<std::string> getAliasList() override;
    };

    /**
     * The @create command.
     */
    class Create : public Command {
     public:
      /**
       * Default constructor.
       */
      Create();

      /**
       * Enact the command.
       */
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;

     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_CREATE_H_
