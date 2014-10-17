/**
 * \file think.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/think.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/functions/iexpressionengine.h"

namespace omush {
  namespace actions {
    Think::Think() {
    }

    void Think::setPlayer(std::shared_ptr<IDatabaseObject> object) {
      player_ = object;
    }

    void Think::setText(library::OString text) {
      text_ = text;
printf(std::string("Test is " + text.plainText() + "\n").c_str());
    }


    void Think::enact(std::shared_ptr<ActionScope> scope) {
      library::OString tempTarget = library::OString(text_);
      scope->queueObject
        ->gameInstance
        ->expressionEngine
        ->parse(tempTarget, makeFunctionScope(scope), tempTarget);

      Notifier::notify(NULL,
                       player_,
                       tempTarget,
                       scope);
    }
  }  // namespace actions
}  // namespace omush
