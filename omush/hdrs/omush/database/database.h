/**
 * \file database.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASE_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASE_H_

#include "omush/database/idatabase.h"
#include <memory>
#include <map>
#include "omush/library/uuid.h"

namespace omush {
  class Database : public IDatabase {
   public:
    Database();
    virtual bool addObject(std::shared_ptr<IDatabaseObject> object) override;
    virtual bool getObjectsByType(DatabaseObjectType type,
                                  UuidToDbObjectMap *map) override;
   private:
    typedef std::map<library::uuid,std::shared_ptr<IDatabaseObject>> UuidToObjectMap;
    typedef std::pair<library::uuid,std::shared_ptr<IDatabaseObject>> UuidToObjectMapPair;
    UuidToObjectMap objectMap_;
    typedef std::map<DatabaseObjectType,UuidToObjectMap> TypeToUuidToObjectMap;
    typedef std::pair<DatabaseObjectType,UuidToObjectMap> TypeToUuidToObjectMapPair;
    TypeToUuidToObjectMap typedObjectMap_;

    void createNewObjectTypeMap(const DatabaseObjectType type);
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASE_H_
