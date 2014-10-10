/**
 * \file add.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FUNCTIONS_FUNCTIONS_ADD_H_
#define OMUSH_HDRS_OMUSH_FUNCTIONS_FUNCTIONS_ADD_H_

#include "omush/functions/ifunction.h"
#include <string>
#include <vector>
#include "omush/library/string.h"
#include "omush/scope.h"

namespace omush {
  namespace functions {
    class AddDefinition : public IFunctionDefinition {
     public:
      AddDefinition() {}
      virtual std::unique_ptr<IFunction> factory() override;
      virtual std::string name() override;
      virtual int maxArgs() override;
      virtual int minArgs() override;
    };

    class Add : public IFunction {
     public:
      Add();
      virtual void execute(std::vector<std::string> args,
                           std::shared_ptr<FunctionScope> scope,
                           library::OString& out) override;
    };
  }  // namespace functions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FUNCTIONS_FUNCTIONS_ADD_H_
