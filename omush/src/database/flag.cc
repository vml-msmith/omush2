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

namespace omush {
  FlagBit FlagDirectory::addFlag(Flag f) {
    std::string name = f.name;
    library::string::to_upper(name);

    if (flagMap.find(f.name) == flagMap.end()) {
      flagMap.insert(std::pair<std::string,Flag>(name, f));
      highBit = highBit << 1;
      f.bit = highBit;
      flagBitMap.insert(std::pair<FlagBit, Flag*>(highBit, &(flagMap[name])));
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
