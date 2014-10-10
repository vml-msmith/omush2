/**
 * \file ifunctin.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FUNCTIONS_IFUNCTION_H_
#define OMUSH_HDRS_OMUSH_FUNCTIONS_IFUNCTION_H_

#include <string>
#include <vector>
#include "omush/library/string.h"
#include "omush/scope.h"

namespace omush {
  class IFunction;
  class IFunctionDefinition {
   public:
    virtual std::string name() = 0;
    virtual int maxArgs() = 0;
    virtual int minArgs() = 0;
    virtual std::unique_ptr<IFunction> factory() = 0;
    virtual std::vector<std::string> getAliasList() {
      return std::vector<std::string>();
    }
  };

  class IFunction {
   public:
    IFunction() {};
    virtual void execute(std::vector<std::string> args,
                         std::shared_ptr<FunctionScope> scope,
                         library::OString& out) = 0;
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FUNCTIONS_IFUNCTION_H_
