/**
 * \file nameformatter.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_NAMEFORMATTER_H_
#define OMUSH_HDRS_OMUSH_DATABASE_NAMEFORMATTER_H_

#include "omush/scope.h"
#include "omush/library/string.h"
#include <iostream>

namespace omush {
  class NameFormatter {
   public:
    enum Flags {
      COLORED = 0x01,
      DBREF = 0x02,
      FLAGS = 0x04,
      IGNORE_HIDDEN = 0x08,
    };

    static void inlineFormat(std::shared_ptr<ActionScope> scope,
                             std::shared_ptr<IDatabaseObject> looker,
                             std::shared_ptr<IDatabaseObject> target,
                             library::OString &string) {
      string = library::OString(target->getName());
    }

    static void format(std::shared_ptr<ActionScope> scope,
                       std::shared_ptr<IDatabaseObject> looker,
                       std::shared_ptr<IDatabaseObject> target,
                       uint64_t flags,
                       library::OString &string) {
      std::string tempString;
      tempString = target->getName();


      std::string endString = "";
      if ((flags && DBREF) == DBREF) {
        endString += "#0";
      }

      if ((flags && FLAGS) == FLAGS) {
        endString += "P";
      }

      if (endString.length() > 0) {
        endString = "(" + endString + ")";
      }
      std::cout << tempString << std::endl;
      string = library::OString(tempString + endString);

      if ((flags && COLORED) == COLORED) {
        // Get the color.
        std::string color = "";
        switch (target->getType()) {
        case DatabaseObjectType::PLAYER:
          color = "red";
          break;
        case DatabaseObjectType::ROOM:
          color = "green";
          break;
        default:
          color = "blue";
        }
        string = library::OString::color(tempString + endString, color);
      }
    }
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_NAMEFORMATTER_H_
