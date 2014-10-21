/**
 * \file powerlist.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/powerlist.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/framework/strings.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/library/log.h"
#include "omush/database/nameformatter.h"
#include "omush/database/utilities.h"

namespace omush {
  namespace actions {
    PowerList::PowerList() : target_(nullptr) {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
      if (hasAddedStrings == false) {
        Strings::ReplaceMap items;

        items["ACTION_POWERLIST__NO_PERMISSION"] =
          "You don't have permission to view that power list.";

        registerStrings_(items);
      }
    }

    void PowerList::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    void PowerList::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::PowerList called without an enactor.");
        return;
      }

      if (target_ == NULL || target_ == nullptr) {
        library::log("action::PowerList called without a target.");
        return;
      }

      if (!hasPowerOver(scope->queueObject->gameInstance->database,
                        enactor_,
                        target_,
                        "Modify")) {
        Notifier::notify(NULL,
                         enactor_,
                         Strings::get("ACTION_POWERLIST__NO_PERMISSION",
                                      scope_),
                         scope);
        return;
      }

      library::string::OString lines = library::OString("");
      library::OString name;
      NameFormatter::format(scope,
                            enactor_,
                            target_,
                            NameFormatter::Flags::POSSESSIVE,
                            name);
      lines += name + " Power List\n--------------------------------------------------------------------------------";
      Notifier::notify(NULL, enactor_, lines, scope);

      std::map<std::string, Power> allPowers = scope->
        queueObject->
        gameInstance->
        database->powers.getAllPowers();
      for (auto& iter : allPowers) {
        std::string msg = "";
        for (int level = 1; level <= 5; ++level) {
          if (hasPowerByBit( scope->
                             queueObject->
                             gameInstance->
                             database, target_, iter.second.bit, level)) {
            msg = scope->
              queueObject->
              gameInstance->
              database->powers.powerToName(&(iter.second), level);
            break;
          }
        }

        if (msg.length() == 0) {
          if (hasPowerByBit(scope->queueObject->gameInstance->database,
                            target_,
                            iter.second.bit,
                            0)) {
            msg = scope->
              queueObject->
              gameInstance->
              database->powers.powerToName(&(iter.second), 0);
          }
        }
        if (msg.length() > 0) {
          Notifier::notify(NULL, enactor_, msg, scope);
        }
      }
      Notifier::notify(NULL,
                       enactor_,
                       library::OString("--------------------------------------------------------------------------------"),
                       scope);

    }


  }  // namespace actions
}  // namespace omush
