/**
 * \file expressionengine.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/functions/expressionengine.h"
#include "omush/database/nameformatter.h"
#include "omush/framework/igameinstance.h"
#include "omush/database/idatabase.h"
#include <iostream>

namespace omush {
  ExpressionEngine::ExpressionEngine() {
  }

  void ExpressionEngine::parse(library::OString in,
                               std::shared_ptr<FunctionScope> scope,
                               library::OString& out) {
    replaceStandardTokens_(in, scope, out);
  }

  void ExpressionEngine::replaceStandardTokens_(library::OString in,
                                                std::shared_ptr<FunctionScope> scope,
                                                library::OString& out) {
    std::shared_ptr<IDatabaseObject> object;

    out = in;
    std::string internalString = in.internalString();
    library::OString name = std::string("Unknown");

    if (scope->queueObject->getExecutorObject(object)) {
      NameFormatter::format(scope->actionScope,
                            object,
                            object,
                            0,
                            name);
    }

    library::string::replace_all(internalString, "%n", name.internalString());
    library::string::replace_all(internalString, "%r", "\n");
    library::string::replace_all(internalString, "%R", "\n");
    library::string::replace_all(internalString, "%t", "    ");
    library::string::replace_all(internalString, "%b", " ");

    out = library::OString(internalString);
  }
}  // namespace omush
