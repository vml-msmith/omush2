/**
 * \file databasematcher.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/databasematcher.h"
#include <map>
#include "omush/library/string.h"


namespace omush {
  DatabaseMatcher::DatabaseMatcher() {
  }

  // TODO(msmith): Right now this only finds player based on the name
  // of the player object. In the future, it needs to look by dbref and
  // alias as well.
  bool DatabaseMatcher::findPlayer(IDatabase *db,
                                   std::string lookupString,
                                   std::shared_ptr<IDatabaseObject>& object) {

    if (db == NULL) {
      return false;
    }

    UuidToDbObjectMap map;
    db->getObjectsByType(PLAYER, &map);


    for (auto iter : map) {
      std::string name = iter.second->getName();
      if (library::string::iequals(name, lookupString)) {
        object = iter.second;
        return true;
      }
    }

    object = NULL;
    return false;
  }
}  // namespace omush
