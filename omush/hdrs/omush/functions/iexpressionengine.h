/**
 * \file iexpressionengine.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FUNCTIONS_IEXPRESSIONENGINE_H_
#define OMUSH_HDRS_OMUSH_FUNCTIONS_IEXPRESSIONENGINE_H_

#include <memory>
#include "omush/library/string.h"
#include "omush/scope.h"

namespace omush {
  class IFunctionDefinition;
  class IExpressionEngine {
   public:
    virtual void parse(library::OString in,
                       std::shared_ptr<FunctionScope> scope,
                       library::OString& out) = 0;
    virtual bool registerFunction(std::shared_ptr<IFunctionDefinition> fun) = 0;
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FUNCTIONS_IEXPRESSIONENGINE_H_
