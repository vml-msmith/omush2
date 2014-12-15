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
      /**
       * @CREATE
       */
      virtual std::string name() override;

      /**
       * @return command::Create
       */
      virtual std::unique_ptr<ICommand> factory() override;

      /**
       * Define the command patterns available.
       *
       *  - @create <object name> 
       *
       * @return vector - List of regex defining the patterns above.
       */
      virtual std::vector<std::string> patterns() override;
    };

    /**
     * The @create command is used to create a new objet of type THING.
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
