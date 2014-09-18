/**
 * \file pose.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_POSE_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_POSE_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/icommand.h"


namespace omush {
  namespace command {
    class PoseDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
    };

    class Pose : public ICommand {
     public:
      Pose();
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_POSE_H_
