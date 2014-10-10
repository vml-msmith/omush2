/**
 * \file expressionengine.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FUNCTIONS_EXPRESSIONENGINE_H_
#define OMUSH_HDRS_OMUSH_FUNCTIONS_EXPRESSIONENGINE_H_

#include "omush/functions/iexpressionengine.h"
#include <memory>
#include "omush/library/string.h"
#include "omush/scope.h"

namespace omush {
  class ExpressionEngine : public IExpressionEngine {
   public:
    ExpressionEngine();
    virtual void parse(library::OString in,
                       std::shared_ptr<FunctionScope> scope,
                       library::OString& out) override;
   private:
    void replaceStandardTokens_(library::OString in,
                                std::shared_ptr<FunctionScope> scope,
                                library::OString& out);
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FUNCTIONS_EXPRESSIONENGINE_H_
