/**
 * \file open.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_OPEN_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_OPEN_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/command.h"
#include "omush/library/string.h"

namespace omush {
  namespace command {
    /**
     * Definition of the Open command.
     */
    class OpenDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
      std::vector<std::string> getAliasList() override;
    };

    /**
     * The @open command.
     */
    class Open : public Command {
     public:
      /**
       * Default constructor.
       */
      Open();

      /**
       * Enact the command.
       */
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;

     private:
      bool openExit_(std::string name,
                     std::shared_ptr<IDatabaseObject> enactor,
                     std::shared_ptr<IDatabaseObject> location,
                     std::shared_ptr<CommandScope> scope,
                     std::shared_ptr<IDatabaseObject>& exit);
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_OPEN_H_
