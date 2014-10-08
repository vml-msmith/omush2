/**
 * \file strings.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_STRINGS_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_STRINGS_H_

#include <string>
#include <map>
#include <memory>
#include "omush/scope.h"
#include "omush/library/string.h"

namespace omush {
  class Strings {
   public:
    typedef std::map<std::string,library::OString> ReplaceMap;

    static library::OString get(std::string key, std::shared_ptr<ActionScope> scope);
    static library::OString get(std::string key, std::shared_ptr<ActionScope> scope, ReplaceMap replacements);
    static library::OString get(std::string key, ReplaceMap replacements);
    static library::OString get(std::string key);
    static Strings& getInstance() {
      static Strings instance;
      return instance;
    }
    library::OString _get(std::string key);
   private:
    std::map<std::string, library::OString> _map;

    Strings();
    Strings(Strings const&);
    void operator=(Strings const&);
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_STRINGS_H_
