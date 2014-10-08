/**
 * \file look.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/look.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/framework/strings.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/library/log.h"

namespace omush {
  namespace actions {
    Look::Look() : player_(nullptr), target_(nullptr) {
    }

    void Look::setPlayer(std::shared_ptr<IDatabaseObject> object) {
      player_ = object;
    }

    void Look::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    void Look::enact(std::shared_ptr<ActionScope> scope) {
      if (player_ == NULL || player_ == nullptr) {
        library::log("action::Look called without an enactor.");
        return;
      }

      if (target_ == NULL || player_ == nullptr) {
        library::log("action::Look called without a target.");
        return;
      }

      library::string::OString lines;
      lines = library::string::OString("You look around...\n");
      // TODO(msmith): This red is wrong.
      Strings::ReplaceMap replacements;
      replacements["!name"] = library::OString::color(target_->getName(), "red");
      lines += Strings::get("You look at .. !name",
                            replacements);
lines += "\n" + library::string::OString::color(target_->getName(), "red");
      Notifier::notify(NULL, player_, lines, scope);
    }

  }  // namespace actions
}  // namespace omush
