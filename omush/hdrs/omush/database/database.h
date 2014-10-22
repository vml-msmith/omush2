/**
 * \file database.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASE_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASE_H_

#include <memory>
#include <map>
#include <utility>
#include "omush/database/idatabase.h"
#include "omush/library/uuid.h"
#include "omush/database/flag.h"

namespace omush {
  class Database : public IDatabase {
   public:
    Database();
    virtual bool addObject(std::shared_ptr<IDatabaseObject> object) override;
    virtual bool getObjectsByType(DatabaseObjectType type,
                                  UuidToDbObjectMap *map) override;
    virtual bool getObjectByUUID(library::uuid uuid,
                                 std::shared_ptr<IDatabaseObject>& object)
      override;
    virtual void getRootUser(std::shared_ptr<IDatabaseObject> &object) override;
    virtual void setRootUser(const std::shared_ptr<IDatabaseObject> object) override;
  private:
    typedef std::map<library::uuid, std::shared_ptr<IDatabaseObject>>
      UuidToObjectMap;
    typedef std::pair<library::uuid, std::shared_ptr<IDatabaseObject>>
      UuidToObjectMapPair;
    UuidToObjectMap objectMap_;
    typedef std::map<DatabaseObjectType, UuidToObjectMap>
      TypeToUuidToObjectMap;
    typedef std::pair<DatabaseObjectType, UuidToObjectMap>
      TypeToUuidToObjectMapPair;
    TypeToUuidToObjectMap typedObjectMap_;
    std::shared_ptr<IDatabaseObject> rootUser_;
    void createNewObjectTypeMap(const DatabaseObjectType type);
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASE_H_
