/**
 * \file add.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/functions/functions/add.h"
#include "omush/functions/expressionengine.h"
#include "omush/library/string.h"
#include <iostream>

namespace omush {
  namespace functions {
    std::string AddDefinition::name() {
      return "add";
    }

    std::unique_ptr<IFunction> AddDefinition::factory() {
      return std::unique_ptr<IFunction>(new Add);
    }

    int AddDefinition::maxArgs() { return 0; }
    int AddDefinition::minArgs() { return 2; }

    Add::Add() {}

    void Add::execute(std::vector<std::string> args,
                      std::shared_ptr<FunctionScope> scope,
                      library::OString& out) {
      std::vector<std::string> parsedArgs;
      for (auto item : args) {
        library::OString oItem;
        scope->queueObject
          ->gameInstance
          ->expressionEngine
          ->parse(item, scope, oItem);
        parsedArgs.push_back(oItem.plainText());
      }

      double total = 0.0;
      for (auto item : parsedArgs) {
        try {
          total += stod(item);
        }
        catch (std::exception) {
          out = "#-1 INVALID ARGUMENTS";
        }
      }
      std::string response = std::to_string(total);
      response = library::string::rtrim(response, "0");
      response = library::string::rtrim(response, ".");
      out = response;
    }

  }  // namespace functions
}  // namespace omush
