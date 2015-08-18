/**
 * \file command.h
 *
 * Copyright 2014 Michael Smith
 */


#ifndef OMUSH_HDRS_OMUSH_COMMANDS_COMMAND_H_
#define OMUSH_HDRS_OMUSH_COMMANDS_COMMAND_H_

#include "omush/commands/icommand.h"
#include <map>
#include <string>
#include "omush/scope.h"
#include "omush/framework/strings.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  class Command : public ICommand {
   public:
    Command() {}
    virtual bool execute(std::shared_ptr<CommandScope> scope) override {
      // TODO(msmith): Why does this need a body here?
      // Undefined symbols for architecture x86_64:
      //   "typeinfo for omush::Command", referenced from:
      //       typeinfo for omush::command::Set in libomush_lib.a(set.cc.o)
      //       typeinfo for omush::command::Go in libomush_lib.a(go.cc.o)
      //       typeinfo for omush::command::Open in libomush_lib.a(open.cc.o)
      //       typeinfo for omush::command::Think in libomush_lib.a(think.cc.o)
      //       typeinfo for omush::command::Create in libomush_lib.a(create.cc.o)
      //       typeinfo for omush::command::Powers in libomush_lib.a(powers.cc.o)
      //       typeinfo for omush::command::Connect in libomush_lib.a(connect.cc.o)
      return true;
    };

   protected:
   /**
    * Parse the patterns of the command into a map of arguments.
    *
    * This method uses a version of regex named groups to regex the possible
    * patterns and pull the matched groups into a map of arguments.
    *
    * @param scope - The CommandScope the command is running in.
    * @param def - The ICommandDefinition of the command that contains patterns.
    * @param matches - Reference to a string keyed map of keys to hold the found
    *                  arguments.
    *
    */
    bool unpackArgs_(std::shared_ptr<CommandScope> scope,
                     ICommandDefinition& def,
                     std::map<std::string,std::string>& matches);
    /**
     * Register a map of std::string => library::OString with Strings library.
     *
     * @param strings - map of std::string => library::OString to register.
     */
    void registerStrings_(Strings::ReplaceMap strings);

    bool getEnactor_(std::shared_ptr<CommandScope> scope,
                     std::shared_ptr<IDatabaseObject> &enactor);
  };

}  // namespace omush

#endif  //  OMUSH_HDRS_OMUSH_COMMANDS_ICOMMAND_H_
