/**
 * \file setflag.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/setflag.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/framework/strings.h"
#include "omush/database/utilities.h"

namespace omush {
  namespace actions {
    SetFlag::SetFlag() {
    }

    void SetFlag::setPlayer(std::shared_ptr<IDatabaseObject> object) {
      player_ = object;
    }

    void SetFlag::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    void SetFlag::setValue(std::string value) {
      value_ = value;
    }

    void SetFlag::enact(std::shared_ptr<ActionScope> scope) {
      bool unset = false;

      if (value_.substr(0,1).c_str()[0] == '!') {
        unset = true;
        value_ = value_.substr(1);
      }

      Flag* flag = scope->queueObject->gameInstance->database->flags.getFlag(value_);
      if (flag == NULL) {
        Notifier::notify(NULL,
                         player_,
                         library::OString(Strings::get("Flag unknown.")),
                         scope);
        return;
      }

      bool hasPermission = true;
      if (!hasOwnershipOfObject(player_, target_)) {
        hasPermission = false;
      }

      if (hasPermission == false) {
      Notifier::notify(NULL,
                       player_,
                       library::OString("Permission denied."),
                       scope);
        return;
      }

      if (unset) {
        unsetFlagOnTarget(flag, scope);
      }
      else {
        setFlagOnTarget(flag, scope);
      }
    }

    void SetFlag::setFlagOnTarget(Flag* flag, std::shared_ptr<ActionScope> scope) {
      std::string str = "set";
      if (hasFlagByBit(target_, flag->bit)) {
        str = "unset";
      }
      addFlagByBit(target_, flag->bit);
      Notifier::notify(NULL,
                       player_,
                       library::OString("Flag " + str + "."),
                       scope);
      Notifier::notify(NULL,
                       target_,
                       library::OString("'" + flag->name + "' flag " + str + "."),
                       scope);
    }

    void SetFlag::unsetFlagOnTarget(Flag* flag, std::shared_ptr<ActionScope> scope) {
      removeFlagByBit(target_, flag->bit);
      Notifier::notify(NULL,
                       player_,
                       library::OString("Flag unset."),
                       scope);
      Notifier::notify(NULL,
                       target_,
                       library::OString("'" + flag->name + "' flag unset."),
                       scope);
    }

  }  // namespace actions
}  // namespace omush
