/**
 * \file power.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/power.h"
#include <string>
#include <vector>
#include <map>
#include "omush/library/string.h"

namespace omush {
  PowerDirectory::PowerDirectory() {
    highBit = 1;
    powerLevels_.push_back("");
    powerLevels_.push_back(", Lower Class");
    powerLevels_.push_back(" In Empire");
    powerLevels_.push_back(" In Empire, Lower Class");
    powerLevels_.push_back(" In Division");
    powerLevels_.push_back(" In Division, Lower Class");
  }

  uint64_t PowerDirectory::add(Power p) {
    std::string name = p.name;
    library::string::to_upper(name);

    if (powerMap.find(name) == powerMap.end()) {
      highBit = highBit << 1;

      p.bit = highBit;

      powerMap.insert(std::pair<std::string, Power>(name, p));

      powerBitMap.insert(std::pair<uint64_t, Power*>(highBit, &(powerMap[name])));
    }

    uint64_t n = powerMap[name].bit;

    return n;
  }

  uint64_t PowerDirectory::getPowerBit(std::string p) {
    std::string name = p;
    library::string::to_upper(name);

    if (powerMap.find(name) == powerMap.end()) {
      return 0;
    }

    return powerMap[name].bit;
  }

  int PowerDirectory::getLevelFromString(std::string p)  {
    int i = -1;
    for (auto key : powerLevels_) {
      ++i;
      if (key.length() == 0)
        continue;

      if (p.length() > key.length()) {
        std::string part = p.substr(p.length() - key.length(), key.length());
        if (library::string::iequals(part, key)) {
          return i;
        }
      }
    }

    return 0;
  }

  std::string PowerDirectory::powerToName(Power *p, int level) {
    if (level < 0 || level > 6)
      return p->name;

    return p->name + powerLevels_[level];
  }

  Power* PowerDirectory::getPower(std::string p) {
    std::string name = p;
    library::string::to_upper(name);

    for (std::string key : powerLevels_) {
      if (key.length() == 0)
        continue;

      if (p.length() > key.length()) {
        std::string part = p.substr(p.length() - key.length(), key.length());
        if (library::string::iequals(part, key)) {
          name = name.substr(0, p.length() - key.length());
        }
      }
    }
    library::string::trim(name, " ");

    if (powerMap.find(name) == powerMap.end()) {
      return NULL;
    }

    return &(powerMap[name]);
  }

  std::map<std::string, Power> PowerDirectory::getAllPowers() {
    return powerMap;
  }
}  // namespace omush
