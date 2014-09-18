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
        std::string value;
      WhoColumn(std::string val, size_t size) : length(size), value(val) {}
      };


      library::OString formatColumns(std::vector<WhoColumn> columns) {
        std::string line = "";

        for (std::vector<WhoColumn>::iterator it = columns.begin();
             it != columns.end();
             ++it) {
          std::string val = (*it).value;
          size_t size = (*it).length;

          if (val.length() > size - 1) {
            val = val.substr(0, size - 1);
          }

          line += val;
          for (int i = 0; i < size - val.length(); ++i) {
            line += " ";
          }
        }

        return library::OString(line);
      }

    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_WHO_H_
