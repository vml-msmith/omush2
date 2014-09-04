/**
 * \file databaseobject.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/databaseobject.h"

namespace omush {
  std::string DatabaseObject::getName() {
    return name_;
  }
}  // namespace omush
