/**
 * \file nameformatter.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/nameformatter.h"

namespace omush {
  void NameFormatter::format(
      std::shared_ptr<ActionScope> scope,
      std::shared_ptr<IDatabaseObject> looker,
      std::shared_ptr<IDatabaseObject> target,
      uint64_t flags,
      library::OString &string) {
    std::string tempString;
    tempString = target->getName();

    if ((flags & POSSESSIVE) == POSSESSIVE) {
      tempString = tempString + "'s";
    }

    std::string endString = "";

    if ((flags & DBREF) == DBREF) {
      endString += "#" + std::to_string(target->getDbref());
    }

    if ((flags & FLAGS) == FLAGS) {
      switch (target->getType()) {
      case DatabaseObjectType::PLAYER:
        endString += "P";
        break;
      case DatabaseObjectType::ROOM:
        endString += "R";
        break;
      case DatabaseObjectType::EXIT:
        endString += "E";
        break;
      default:
        endString += "T";
      }
    }

    if (endString.length() > 0) {
      endString = "(" + endString + ")";
    }

    string = library::OString(tempString + endString);

    if ((flags & COLORED) == COLORED) {
      // Get the color.
      std::string color = "";
      switch (target->getType()) {
      case DatabaseObjectType::PLAYER:
        color = "red";
        break;
      case DatabaseObjectType::ROOM:
        color = "green";
        break;
      case DatabaseObjectType::EXIT:
        color = "cyan";
        break;
      default:
        color = "blue";
      }
      string = library::OString::color(tempString + endString, color);
    }
  }
}  // namespace  omush
