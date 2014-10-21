/**
 * \file nameformatter.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_NAMEFORMATTER_H_
#define OMUSH_HDRS_OMUSH_DATABASE_NAMEFORMATTER_H_

#include "omush/scope.h"
#include "omush/library/string.h"
#include "omush/database/IDatabaseObject.h"

namespace omush {
  class NameFormatter {
   public:
    enum Flags {
      COLORED       = 0x0001,
      DBREF         = 0x0002,
      FLAGS         = 0x0004,
      POSSESSIVE    = 0x0008,
      IGNORE_HIDDEN = 0x0010,
    };

    static void inlineFormat(std::shared_ptr<ActionScope> scope,
                             std::shared_ptr<IDatabaseObject> looker,
                             std::shared_ptr<IDatabaseObject> target,
                             library::OString &string) {
      NameFormatter::format(scope, looker, target, 0, string);
      string = library::OString(target->getName());
    }

    static void format(std::shared_ptr<ActionScope> scope,
                       std::shared_ptr<IDatabaseObject> looker,
                       std::shared_ptr<IDatabaseObject> target,
                       uint64_t flags,
                       library::OString &string);
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_NAMEFORMATTER_H_
