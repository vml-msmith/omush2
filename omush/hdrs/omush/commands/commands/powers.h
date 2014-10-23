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
    /**
     * Definition of the Powers command.
     */
    class PowersDefinition : public ICommandDefinition {
     public:
      virtual std::string name() override;
      virtual std::unique_ptr<ICommand> factory() override;
      virtual std::vector<std::string> patterns() override;
      std::vector<std::string> getAliasList() override;
    };

    /**
     * The @powers command.
     *
     * List Powers per target
     *   @powers - Show powers of self.
     *   @powers <target> - Show powers of target.
     *
     * Add Power
     *   @powers/[add|grant] <target>=<Power Name>
     *   @powers/[add|grant] <target>=<Power Name>/<int level>
     *
     * Remove Power
     *   @powers/[remove|revoke] <target>=<power name>
     */
    class Powers : public Command {
     public:
      /**
       * Default constructor.
       */
      Powers();

      /**
       * Enact the command.
       */
      virtual bool execute(std::shared_ptr<CommandScope> scope) override;

     private:
      /**
       * Get the target DataaseObject from the <target> portion of the command.
       *
       * @param scope - Shared pointer to the scope of the command.
       * @param targetString - The <target> poition of the command.
       * @param looker - The enactor of the command.
       * @param target - OUT: A shared_ptr to the target found.
       * @param error - OUT: A reference to an error string when the target
       *                can't be found.
       *
       * @return - True (success, found a target)
       *         - False (failure, didn't find a target)
       */
      bool getTarget_(std::shared_ptr<CommandScope> scope,
                      std::string targetString,
                      std::shared_ptr<IDatabaseObject> looker,
                      std::shared_ptr<IDatabaseObject> &target,
                      library::OString &error);

      /**
       * Explode the argument after the equals sign into both a Power name
       * and a power level if it's there.
       *
       * @param input - The porition of the command to the right of the "=".
       * @param powerString - Refernce to a string that is the power name.
       * @param powerLevel = an integer between 0 - 5 that is the power level.
       */
      void explodeInputToPowerStringAndLevel_(const std::string input,
                                              std::string &powerString,
                                              int &powerLevel);
    };
  }  // namespace command
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_COMMANDS_COMMANDS_POWERS_H_
