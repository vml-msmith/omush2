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
    virtual bool registerFunction(std::shared_ptr<IFunctionDefinition> fun) override;
   private:
    void processExpression_(library::OString in,
                            std::shared_ptr<FunctionScope> scope,
                            library::OString& out);
    void replaceStandardTokens_(library::OString in,
                                std::shared_ptr<FunctionScope> scope,
                                library::OString& out);
    std::map<std::string,std::shared_ptr<IFunctionDefinition>> functions_;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FUNCTIONS_EXPRESSIONENGINE_H_
