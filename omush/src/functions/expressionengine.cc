/**
 * \file expressionengine.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/functions/expressionengine.h"
#include "omush/functions/ifunction.h"
#include "omush/database/nameformatter.h"
#include "omush/framework/igameinstance.h"
#include "omush/database/idatabase.h"
#include <iostream>

namespace omush {
  ExpressionEngine::ExpressionEngine() {
  }

  bool ExpressionEngine::registerFunction(std::shared_ptr<IFunctionDefinition> fun)  {

functions_.insert(std::pair<std::string, std::shared_ptr<IFunctionDefinition>>(fun->name(), fun));
    return true;
  }
  void ExpressionEngine::parse(library::OString in,
                               std::shared_ptr<FunctionScope> scope,
                               library::OString& out) {
    //    scope.trace = true;
    std::cout << "parse " << in.plainText() << std::endl;
    processExpression_(in, scope, out);
    std::cout << "End: " << out.plainText() << std::endl;
    replaceStandardTokens_(out, scope, out);
  }

  std::vector<std::string> splitArgs_(std::string str) {
    std::vector<std::string> response;
    const char *c = str.c_str();
    std::string arg = "";

    char seek = '\0';
    char currentChar = '\0';
    int depth = 0;

    while (*c) {
      if (*c == ',' && seek == '\0') {
        response.push_back(arg);
        arg = "";
      }
      else {
        if (seek == '\0') {
          currentChar = *c;
          ++depth;
          switch (*c) {
          case '[':
            seek = ']';
            break;
          case '(':
            seek = ')';
            break;
          default:
            --depth;
            currentChar = '\0';
            break;
          }
        }
        else if (*c == seek) {
          --depth;
          if (depth == 0) {
            seek = '\0';
            currentChar = '\0';
          }
        }
        else if (*c == currentChar) {
          ++depth;
        }
        arg += *c;
      }

      *++c;
    }
    response.push_back(arg);
    return response;
  }

  std::string findSelfContainedExpression_(std::string str) {
    const char *c = str.c_str();
    std::string response;

    char seek = '\0';
    char currentChar = '\0';
    int depth = 0;
    while (*c) {
      if (seek == '\0') {
        currentChar = *c;
        ++depth;
        switch (*c) {
        case '[':
          seek = ']';
          //          ++depth;
          break;
        case '(':
          seek = ')';
          // ++depth;
          break;
        default:
          //          seek = '[';
          // ++depth;
          --depth;
          currentChar = '\0';
          break;
        }
      }
      else if (*c == seek) {
        --depth;
        if (depth == 0) {
          if (seek != '[') {
            response += *c;
          }
          break;
        }
      }
      else if (*c == currentChar) {
        ++depth;
      }

      response += *c;
      *++c;
    }

    return response;
  }

  void printStr(std::string str, std::shared_ptr<FunctionScope> scope) {
    std::string line = "";
    for (int i = 0; i < scope->depth; ++i) {
      line += " ";
    }
    line += "#0: " + str;
    std::cout << line << std::endl;
  }

  void ExpressionEngine::processExpression_(library::OString in,
                                            std::shared_ptr<FunctionScope> scope,
                                            library::OString& out) {
    ++scope->depth;
    std::string internalString = in.internalString();
    printStr(internalString, scope);
    std::string finished = "";

    std::vector<std::string> sections;

    while (internalString.length() > 0) {
      std::string selfContained = findSelfContainedExpression_(internalString);
      sections.push_back(selfContained);
      internalString = internalString.substr(selfContained.length());
    }

    for (auto item : sections) {

      if (item.substr(0,1).c_str()[0] == '[') {
        item = item.substr(1, item.length() - 2);
        // Strip the braces and run it again!
        processExpression_(item, scope, out);

        item = out.internalString();
      }
      else {
        // Find the first occurance of ( or [.
        std::size_t pos = item.find_first_of("(");
        if (pos != std::string::npos) {
          if (item[pos] == '(') {
            // cut off any spaces, add to finished.
            // lowercase it just in case.
            std::string methodName = item.substr(0,pos);
            if (functions_.find(methodName) == functions_.end()) {
              item = "#-1 NOT FOUND";
            }
            else {
              std::unique_ptr<IFunction> fun = functions_[methodName]->factory();

              std::cout << "Method: " << methodName << std::endl;
              std::string theRest = item.substr(pos + 1, item.length() - pos - 2);
              std::vector<std::string> args = splitArgs_(theRest);
              for (auto a : args) {
                printStr("Arg: " + a, scope);
              }
              library::OString bit;
              fun->execute(args, scope, bit);
              //          std::cout << "Rest: " << theRest << std::endl;
              item = bit.plainText();
            }
          }
        }
        else {
          // There is nothing to do, this thing is done.
        }
      }

      finished += item;
    }


    //    if (self
    --scope->depth;
    printStr(in.internalString(), scope);
    out = library::OString(finished);


    /*
    const char *c = in.internalString().c_str();
    std::cout << "Process " << in.internalString().c_str() << std::endl;
    int start = -1;
    int end = -1;

    int count = 0;
    int pos = 0;
    char next = '\0';
    char current = '\0';

    while (*c) {
      std::cout << "While: " << *c << std::endl;
      if (next == '\0') {
        if (*c == '[') {
          start = pos;
          next = ']';
          current = *c;
          ++pos;
          *c++;
          std::cout << " 1" << std::endl;
          continue;
        }
        if (*c == '(') {
          start = pos;
          next = ')';
          current = *c;
          ++pos;
          *c++;
          std::cout << " 2" << std::endl;
          continue;
        }
      }
      else {
        if (next == *c) {
          if (count == 0) {
            end = pos;
          std::cout << " 3" << std::endl;
            break;
          }
          else {
            --count;
            ++pos;
            *c++;
          std::cout << " 4" << std::endl;
            continue;
          }
        }
        else if (current == *c) {
          ++count;
          std::cout << " 5" << std::endl;
        }
      }
          std::cout << " 6" << std::endl;
      ++pos;
      std::cout << "now is : " << *c << std::endl;
      *c++;
      std::cout << "next is : " << *c << std::endl;
    }
    *c++;
      std::cout << "next would be : " << *c << std::endl;

    if (end == -1) {
      replaceStandardTokens_(in, scope, out);
      //      str = runReplacements(str, context);
      std::cout << "Out early." << std::endl;
      return;
    }

    if (start > 0 && /*context.limit > 0*//*true) {
      const char *s = in.internalString().c_str();
      for (int i = 0; i < start; ++i) {
        if (*s == ' ') {
          replaceStandardTokens_(in, scope, out);
      //      #include <string> = runReplacements(str, context);
      std::cout << "Out late.." << std::endl;
          return;
        }
        *s++;
      }
    }

    int final = (end + 1) - start;
    int begin = start;

    std::cout << " Out final " << std::endl;
    library::OString response = library::OString(in.internalString().substr(start, final));
                                          */
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
