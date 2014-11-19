/**
 * \file shutdown.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/shutdown.h"
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
    Shutdown::Shutdown() : isReboot_(false) {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
      if (hasAddedStrings == false) {
        Strings::ReplaceMap items;
        items["ACTION_SHUTDOWN__PERMISSION_DENIED"] =
          "Permission denied.";
        registerStrings_(items);
      }
    }

    void Shutdown::setReboot(bool isReboot) {
      isReboot_ = isReboot;
    }

    bool Shutdown::hasPermission_(std::shared_ptr<ActionScope> scope) {
      std::string requiredPower = "Shutdown";
      if (!isRootUser(scope->queueObject->gameInstance->database,
                      enactor_) &&
          !hasPower(scope->queueObject->gameInstance->database,
                    enactor_,
                    requiredPower)) {
        return false;
      }

      return true;
    }

    library::OString Shutdown::makeString(std::shared_ptr<IDatabaseObject> object) {
      /*
      if (object == player_)
        return library::OString("You say, \"") + text_ + library::OString("\"");

      library::OString name;
      NameFormatter::inlineFormat(scope_,
                                  object,
                                  player_,
                                  name);
      return name + library::OString(" says, \"") + text_ + library::OString("\"");
      */
      return library::OString("Going down!");
    }

    void Shutdown::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::Shutdown called without an enactor.");
        return;
      }


      if (!hasPermission_(scope)) {
        Notifier::notify(NULL,
                         enactor_,
                         Strings::get("ACTION_SHUTDOWN__PERMISSION_DENIED",
                                      scope),
                         scope);
        return;
      }

      Notifier::notifyAllOfType(scope->queueObject->gameInstance->database,
                                DatabaseObjectType::PLAYER,
                                boost::bind(&omush::actions::Shutdown::makeString,
                                            this,
                                            ::_1),
                                scope);

      Notifier::notify(NULL,
                       enactor_,
                       Strings::get("Shutdown...",scope),
                       scope);

      // Trigger 'shutdown' attribute on all objects.
      //
      if (isReboot_) {
        scope->queueObject->gameInstance->game->reboot();
      } else {
        scope->queueObject->gameInstance->game->shutdown();
      }
    }

  }  // namespace actions
}  // namespace omush
