/**
 * \file idatabase.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_IDATABASE_H_
#define OMUSH_HDRS_OMUSH_DATABASE_IDATABASE_H_

#include <map>
#include <memory>
#include "omush/library/uuid.h"
#include "omush/database/flag.h"

namespace omush {
  enum DatabaseObjectType { THING = 0, PLAYER = 1, ROOM = 2 };
  class IDatabaseObject;
  typedef std::map<library::uuid,std::shared_ptr<IDatabaseObject>> UuidToDbObjectMap;

  class IDatabase {
   public:
    IDatabase() {};
    virtual bool addObject(std::shared_ptr<IDatabaseObject> object) = 0;
    virtual bool getObjectByUUID(library::uuid uuid,
                                 std::shared_ptr<IDatabaseObject>& object) = 0;
    virtual bool getObjectsByType(DatabaseObjectType type,
                                  UuidToDbObjectMap *map) = 0;
    FlagDirectory flags;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_IDATABASE_H_
