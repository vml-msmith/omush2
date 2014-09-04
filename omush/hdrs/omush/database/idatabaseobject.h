/**
 * \file idatabaseobject.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_IDATABASEOBJECT_H_
#define OMUSH_HDRS_OMUSH_DATABASE_IDATABASEOBJECT_H_

#include <string>

namespace omush {
  class IDatabaseObject {
   public:
    IDatabaseObject() {};
    virtual std::string getName() = 0;
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_IDATABASEOBJECT_H_
