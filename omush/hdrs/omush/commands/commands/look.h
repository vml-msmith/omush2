/**
 * \file look.h
 *
 * Copyright 2014 Michael Smith
 */


#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_LOOK_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_LOOK_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/icommand.h"

namespace omush {
  namespace command {
    class LookDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
    };

    class Look : public ICommand {
     public:
      Look();
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_LOOK_H_
