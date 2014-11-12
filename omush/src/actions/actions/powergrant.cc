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

    bool PowerGrant::hasPermission_(std::shared_ptr<ActionScope> scope,
                                    Power* power,
                                    int level) {
      std::string requiredPower = "Power Grant";

      if (!isRootUser(scope->queueObject->gameInstance->database,
                      enactor_) &&
          !hasPowerOver(scope->queueObject->gameInstance->database,
                        enactor_,
                        target_,
                        requiredPower)) {
        return false;
      }

      if (!isRootUser(scope->queueObject->gameInstance->database,
                      enactor_) &&
          !hasPowerByBit(scope->queueObject->gameInstance->database,
                         enactor_,
                         power->bit,
                         powerLevel_)) {
        return false;
      }

      return true;

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

      if (!hasPermission_(scope, p, powerLevel_)) {
        Notifier::notify(NULL,
                         enactor_,
                         Strings::get("ACTION_POWERGRANT__NO_PERMISSION",
                                      scope),
                         scope);
      }


      addPowerByBit(target_, p->bit, powerLevel_);
      notifyEnactor_(scope, p);
      notifyTarget_(scope, p);
    }

    void PowerGrant::notifyTarget_(std::shared_ptr<ActionScope> scope,
                                   Power* power) {
      std::string pName = scope->
        queueObject->
        gameInstance->
        database->powers.powerToName(power, powerLevel_);

      Notifier::notify(NULL,
                       target_,
                       library::OString("'" + pName + "' granted by " + enactor_->getName() + "."),
                       scope);
    }

    void PowerGrant::notifyEnactor_(std::shared_ptr<ActionScope> scope,
                                    Power* power) {
      std::string pName = scope->
        queueObject->
        gameInstance->
        database->powers.powerToName(power, powerLevel_);

      Notifier::notify(NULL,
                       enactor_,
                       library::OString(target_->getName() + " -- \"" + pName + "\" granted."),
                       scope);
    }

  }  // namespace actions
}  // namespace omush
