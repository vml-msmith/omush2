/**
 * \file databaseobject.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/databaseobject.h"
#include <string>
#include "omush/library/uuid.h"

namespace omush {
  std::string DatabaseObject::getName() const {
    return name_;
  }

  void DatabaseObject::setName(std::string name) {
    name_ = name;
  }

  library::uuid DatabaseObject::getUuid() const {
    return uuid_;
  }

  DatabaseObjectType DatabaseObject::getType() const {
    return type_;
  }

  void DatabaseObject::setLocation(std::shared_ptr<IDatabaseObject> location) {
    if (location == nullptr)
      return;

    location_ = location;
  }

  void DatabaseObject::getLocation(std::shared_ptr<IDatabaseObject> &location) {
    if (location_ == nullptr)
      return;
    else
      location = location_;
  }


}  // namespace omush
