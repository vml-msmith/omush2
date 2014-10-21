/**
 * \file powers.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_POWERS_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_POWERS_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/command.h"
#include "omush/library/string.h"

namespace omush {
  namespace command {
    class PowersDefinition : public ICommandDefinition {
    public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
    };

    class Powers : public Command {
     public:
      Powers();
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
      bool _getTarget(std::shared_ptr<CommandScope> scope,
                      std::string targetString,
                      std::shared_ptr<IDatabaseObject> looker,
                      std::shared_ptr<IDatabaseObject> &target,
                      library::OString &error);
  };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_POWERS_H_
