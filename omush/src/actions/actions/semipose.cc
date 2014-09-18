/**
 * \file semipose.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/semipose.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/database/nameformatter.h"

namespace omush {
  namespace actions {
    SemiPose::SemiPose() {
    }

    void SemiPose::setPlayer(std::shared_ptr<IDatabaseObject> object) {
      player_ = object;
    }

    void SemiPose::setText(std::string text) {
      text_ = text;
    }

    library::OString SemiPose::makeString(std::shared_ptr<IDatabaseObject> object) {
      if (object == player_)
        return library::OString("You" + text_);

      library::OString name;
      NameFormatter::inlineFormat(scope_,
                                  object,
                                  player_,
                                  name);
      return name + library::OString(text_);
    }

    void SemiPose::enact(std::shared_ptr<ActionScope> scope) {
      scope_ = scope;
      // Parse the text_.

      Notifier::notifySurroundings(NULL,
                                   player_,
                                   boost::bind(&omush::actions::SemiPose::makeString,
                                               this,
                                               ::_1),
                                   scope);


    }
  }  // namespace actions
}  // namespace omush
