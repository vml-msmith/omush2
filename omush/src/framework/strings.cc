/**
 * \file strings.cc
 *
 * Copyright 2014 Michael Smith
 */
#include "omush/framework/strings.h"
#include "omush/scope.h"
#include <boost/algorithm/string/replace.hpp>

namespace omush {
  library::OString Strings::get(std::string key,
                                std::shared_ptr<ActionScope> scope) {
    ReplaceMap replacements;
    // TODO: add scope to replacements.
    return Strings::get(key, replacements);
  }

  library::OString Strings::get(std::string key,
                                std::shared_ptr<ActionScope> scope,
                                ReplaceMap replacements) {
    // TODO: Add scope to replacements.
    return Strings::get(key, replacements);
  }

  library::OString Strings::get(std::string key,
                                ReplaceMap replacements) {
    Strings &s = Strings::getInstance();
    library::OString outString = s._get(key);
    std::string internalString = outString.internalString();
    for (auto& item : replacements) {
      boost::algorithm::replace_all(internalString,
                                    item.first,
                                    item.second.internalString());
    }

    return library::OString(internalString);
  }

  library::OString Strings::get(std::string key) {
    ReplaceMap replacements;
    // TODO: add scope to replacements.
    return Strings::get(key, replacements);
  }

  library::OString Strings::_get(std::string key) {
    if (_map.find(key) == _map.end())
      return "STRING_NOT_FOUND: " + key;

    // TODO(msmith): Updates.
    // Count it?
    // Maybe look to see if it's soft coded.
    return _map.find(key)->second;
  }

  Strings::Strings() {
    // TODO(msmith): Localize 'em.
    _map.insert(std::pair<std::string,std::string>("COMMAND_NOT_FOUND", "I don't recognize that command."));
  }

}  // namespace omush
