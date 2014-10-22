/**
 * \file powergrant.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/powergrant.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/framework/strings.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/library/log.h"
#include "omush/database/nameformatter.h"
#include "omush/database/utilities.h"
#include <iostream>

namespace omush {
  namespace actions {
    PowerGrant::PowerGrant() : target_(nullptr), powerString_(""), powerLevel_(0) {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
      if (hasAddedStrings == false) {
        Strings::ReplaceMap items;
        /*
        items["ACTION_CONNECT__YOU_HAVE_CONNECTED"] =
          "You have connected...";
        items["ACTION_CONNECT__OTHER_HAS_CONNECTED"] =
          "!playerName has connected.";
        */
        registerStrings_(items);
      }
    }

    void PowerGrant::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    void PowerGrant::setPowerString(std::string powerString) {
      powerString_ = powerString;
    }

    void PowerGrant::setPowerLevel(int level) {
      powerLevel_ = level;
    }

    void PowerGrant::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::PowerGrant called without an enactor.");
        return;
      }

      if (target_ == NULL || target_ == nullptr) {
        library::log("action::PowerGrant called without a target.");
        return;
      }

      if (!isRootUser(scope->queueObject->gameInstance->database,
                      enactor_) &&
          !hasPowerOver(scope->queueObject->gameInstance->database,
                        enactor_,
                        target_,
                        "Power Grant")) {
        Notifier::notify(NULL,
                         enactor_,
                         Strings::get("ACTION_POWERGRANT__NO_PERMISSION",
                                      scope),
                         scope);
        return;
      }

      Power* p = scope->
        queueObject->
        gameInstance->
        database->
        powers.getPower(powerString_);

      if (p == NULL) {
        Notifier::notify(NULL,
                         enactor_,
                         Strings::get("ACTION_POWERGRANT__INVALID_POWER",
                                      scope),
                         scope);
        return;
      }

      if (powerLevel_ < 0 || powerLevel_ > 5) {
        Notifier::notify(NULL,
                         enactor_,
                         Strings::get("ACTION_POWERGRANT__INVALID_LEVEL",
                                      scope),
                         scope);
      }


      if (!isRootUser(scope->queueObject->gameInstance->database,
                      enactor_) &&
          !hasPowerByBit(scope->queueObject->gameInstance->database,
                         enactor_,
                         p->bit,
                         powerLevel_)) {
        Notifier::notify(NULL,
                         enactor_,
                         Strings::get("ACTION_POWERGRANT__NO_PERMISSION",
                                      scope),
                         scope);
        return;
      }

      addPowerByBit(target_, p->bit, powerLevel_);

      Notifier::notify(NULL,
                       enactor_,
                       library::OString(target_->getName() + " -- Power granted."),
                       scope);
      std::string pName = scope->
        queueObject->
        gameInstance->
        database->powers.powerToName(p, powerLevel_);

      Notifier::notify(NULL,
                       target_,
                       library::OString("'" + pName + "' granted by " + enactor_->getName() + "."),
                       scope);
    }


  }  // namespace actions
}  // namespace omush
