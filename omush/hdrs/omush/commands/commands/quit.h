/**
 * \file quit.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_QUIT_H_
#define HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_QUIT_H_

#include "omush/commands/icommand.h"

namespace omush {
  namespace command {
    class QuitDefinition : public ICommandDefinition {
      virtual std::string name();
      virtual ICommand* factory();
    };

    class Quit : public ICommand {
     public:
      Quit();
     private:
    };
  }  // namespace command
}  // namespace omush

#endif  // HDRS_OMUSH_HDRS_COMMANDS_COMMANDS_QUIT_H_
