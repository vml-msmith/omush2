/**
 * \file say.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/say.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/database/nameformatter.h"

namespace omush {
  namespace actions {
    Say::Say() {
    }

    void Say::setPlayer(std::shared_ptr<IDatabaseObject> object) {
      player_ = object;
    }

    void Say::setText(library::OString text) {
      text_ = text;
    }

    library::OString Say::makeString(std::shared_ptr<IDatabaseObject> object) {
      if (object == player_)
        return library::OString("You say, \"") + text_ + library::OString("\"");

      library::OString name;
      NameFormatter::inlineFormat(scope_,
                                  object,
                                  player_,
                                  name);
      return name + library::OString(" says, \"") + text_ + library::OString("\"");
    }

    void Say::enact(std::shared_ptr<ActionScope> scope) {
        scope_ = scope;
      // Parse the text_.

      Notifier::notifySurroundings(NULL,
                                   player_,
                                   boost::bind(&omush::actions::Say::makeString,
                                               this,
                                               ::_1),
                                   scope);


    }
  }  // namespace actions
}  // namespace omush
