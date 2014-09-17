/**
 * \file look.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/look.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/string.h"
#include "omush/notifier.h"

namespace omush {
  namespace actions {
    Look::Look() {
    }

    void Look::setPlayer(std::shared_ptr<IDatabaseObject> object) {
      player_ = object;
    }

    void Look::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    void Look::enact(std::shared_ptr<ActionScope> scope) {
      omush::library::string::OString lines = omush::library::string::OString("You look around....\n");
      lines += library::string::OString::color(target_->getName(), "red");
      Notifier::notify(NULL, player_, lines, scope);
    }

  }  // namespace actions
}  // namespace omush
