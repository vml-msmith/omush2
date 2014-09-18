/**
 * \file pose.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/pose.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/database/nameformatter.h"

namespace omush {
  namespace actions {
    Pose::Pose() {
    }

    void Pose::setPlayer(std::shared_ptr<IDatabaseObject> object) {
      player_ = object;
    }

    void Pose::setText(std::string text) {
      text_ = text;
    }

    library::OString Pose::makeString(std::shared_ptr<IDatabaseObject> object) {
      if (object == player_)
        return library::OString("You " + text_);

      // TODO(msmith): Format this name.
      library::OString name;
      NameFormatter::inlineFormat(scope_,
                                  object,
                                  player_,
                                  name);

      return name + library::OString(" " + text_);
    }

    void Pose::enact(std::shared_ptr<ActionScope> scope) {
      scope_ = scope;
      // Parse the text_.

      Notifier::notifySurroundings(NULL,
                                   player_,
                                   boost::bind(&omush::actions::Pose::makeString,
                                               this,
                                               ::_1),
                                   scope);


    }
  }  // namespace actions
}  // namespace omush
