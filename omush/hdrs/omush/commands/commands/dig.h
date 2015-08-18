/**
 * \file dig.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_DIG_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_DIG_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/command.h"
#include "omush/library/string.h"

namespace omush {
  namespace command {
    /**
     * Definition of the Dig command.
     */
    class DigDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
      std::vector<std::string> getAliasList() override;
    };

    /**
     * The @dig command.
     */
    class Dig : public Command {
     public:
      /**
       * Default constructor.
       */
      Dig();

      /**
       * Enact the command.
       */
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;

    private:
      /*
      bool openExit_(std::string name,
                     std::shared_ptr<IDatabaseObject> enactor,
                     std::shared_ptr<IDatabaseObject> location,
                     std::shared_ptr<CommandScope> scope,
                     std::shared_ptr<IDatabaseObject>& exit);
      */
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_DIG_H_
