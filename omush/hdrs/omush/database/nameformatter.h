/**
 * \file nameformatter.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_NAMEFORMATTER_H_
#define OMUSH_HDRS_OMUSH_DATABASE_NAMEFORMATTER_H_

#include "omush/scope.h"
#include "omush/library/string.h"

namespace omush {
  class NameFormatter {
   public:
    static void inlineFormat(std::shared_ptr<ActionScope> scope,
                             std::shared_ptr<IDatabaseObject> looker,
                             std::shared_ptr<IDatabaseObject> target,
                             library::OString &string) {
      printf("Here\n");
      string = library::OString(target->getName());
      printf("Here2\n");
    }
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_NAMEFORMATTER_H_
