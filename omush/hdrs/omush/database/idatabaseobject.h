/**
 * \file idatabaseobject.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_IDATABASEOBJECT_H_
#define OMUSH_HDRS_OMUSH_DATABASE_IDATABASEOBJECT_H_

#include <string>
#include "omush/library/uuid.h"
#include "omush/database/idatabase.h"

namespace omush {
  class IDatabaseObject {
   public:
    IDatabaseObject() {};
    virtual std::string getName() const = 0;
    virtual library::uuid getUuid() const = 0;
    virtual DatabaseObjectType getType() const = 0;
    virtual void setName(std::string name) = 0;
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_IDATABASEOBJECT_H_
