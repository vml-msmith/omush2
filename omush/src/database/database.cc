/**
 * \file database.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/database.h"

namespace omush {
  Database::Database() {
  }

  bool Database::getObjectsByType(DatabaseObjectType type, UuidToDbObjectMap *map) {
    if (map == NULL) {
      return false;
    }

    TypeToUuidToObjectMap::iterator iter = typedObjectMap_.find(type);

    if (iter == typedObjectMap_.end()) {
      return false;
    }

    map->insert(iter->second.begin(), iter->second.end());

    return true;
  }

  bool Database::addObject(std::shared_ptr<IDatabaseObject> object) {
  }

}  // namespace omush
