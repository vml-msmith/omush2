/**
 * \file database.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/database.h"
#include "omush/database/databaseobject.h"
#include <boost/uuid/uuid_io.hpp>

namespace omush {
  Database::Database() : topDbref_(0) {
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

  bool Database::getObjects(UuidToDbObjectMap *map) {
    for (auto &iter : typedObjectMap_) {
      map->insert(iter.second.begin(), iter.second.end());
    }
  }

  bool Database::addObject(std::shared_ptr<IDatabaseObject> object) {
    objectMap_.insert(UuidToObjectMapPair(object->getUuid(), object));

    DatabaseObjectType type = object->getType();
    TypeToUuidToObjectMap::iterator iter = typedObjectMap_.find(type);
    if (iter == typedObjectMap_.end()) {
      this->createNewObjectTypeMap(type);
      iter = typedObjectMap_.find(type);
    }

    iter->second.insert(UuidToObjectMapPair(object->getUuid(), object));


    dbrefToUuidMap_.insert(DbrefToUuidMapPair(object->getDbref(), object->getUuid()));

    if (object->getDbref() >= topDbref_) {
      topDbref_ = object->getDbref();
    }
  }

  void Database::createNewObjectTypeMap(const DatabaseObjectType type) {
    typedObjectMap_.insert(TypeToUuidToObjectMapPair(type,
                                                     UuidToObjectMap()));
  }

  bool Database::getObjectByUUID(library::uuid uuid,
                                 std::shared_ptr<IDatabaseObject>& object)  {
    UuidToObjectMap::iterator iter = objectMap_.find(uuid);
    if (iter == objectMap_.end()) {
      object = nullptr;
      return false;
    }

    object = iter->second;
    return true;
  }


  bool Database::getObjectByDbref(Dbref dbref,
                                  std::shared_ptr<IDatabaseObject>& object) {
    DbrefToUuidMap::iterator iter = dbrefToUuidMap_.find(dbref);
    if (iter == dbrefToUuidMap_.end()) {
      object = nullptr;
      return false;
    }

    return getObjectByUUID(iter->second, object);
  }

  void Database::getRootUser(std::shared_ptr<IDatabaseObject> &object) {
    object = rootUser_;
  }

  void Database::setRootUser(const std::shared_ptr<IDatabaseObject> object) {
    rootUser_ = object;
  }

  Dbref Database::getNextDbref() {
    return topDbref_ + 1;
  }
}  // namespace omush
