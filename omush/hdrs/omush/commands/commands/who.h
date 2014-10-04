/**
 * \file who.h
 *
 * Copyright 2014 Michael Smith
 */


#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_WHO_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_WHO_H_

#include <memory>
#include <string>
#include <vector>
#include "omush/commands/icommand.h"
#include "omush/library/string.h"
#include "omush/library/time.h"

namespace omush {
  namespace command {
    class WhoDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
    };

    class Who : public ICommand {
     public:
      Who();
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;
     private:
      struct WhoColumn {
        size_t length;
        library::OString value;
      WhoColumn(library::OString val, size_t size) : length(size), value(val) {}
      };

      library::OString formatOnFor(library::time_duration time);
      library::OString formatIdle(library::time_duration time);
      library::OString formatColumns(std::vector<WhoColumn> columns);
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_WHO_H_
