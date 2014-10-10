/**
 * \file flag.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/flag.h"
#include <string>
#include <vector>
#include <map>
#include "omush/library/string.h"
#include <iostream>

namespace omush {
  FlagDirectory::FlagDirectory() {
    highBit = 1;
  }

  FlagBit FlagDirectory::addFlag(Flag f) {
    std::string name = f.name;
    library::string::to_upper(name);

    if (flagMap.find(f.name) == flagMap.end()) {
      highBit = highBit << 1;
      f.bit = highBit;
      flagMap.insert(std::pair<std::string,Flag>(name, f));
      flagBitMap.insert(std::pair<FlagBit, Flag*>(highBit,
                                                  &(flagMap[name])));
    }

    return flagMap[name].bit;
  }

  FlagBit FlagDirectory::getFlagBit(std::string f) {
    std::string name = f;
    library::string::to_upper(name);

    if (flagMap.find(name) == flagMap.end()) {
      return 0;
    }

    return flagMap[name].bit;
  }

  Flag* FlagDirectory::getFlag(std::string f) {
    std::string name = f;
    library::string::to_upper(name);

    if (flagMap.find(name) == flagMap.end()) {
      return NULL;
    }

    return &(flagMap[name]);
  }

  FlagDirectory::FlagMap FlagDirectory::getAllFlags() {
    return flagMap;
  }
}  // namespace omush
