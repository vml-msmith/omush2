/**
 * \file strings.cc
 *
 * Copyright 2014 Michael Smith
 */
#include "omush/framework/strings.h"

namespace omush {
  std::string Strings::get(std::string key) {
        Strings &s = Strings::getInstance();
    return s._get(key);
  }

  std::string Strings::_get(std::string key) {
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
