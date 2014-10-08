/**
 * \file databaseobject.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECT_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECT_H_

#include <memory>
#include <string>

#include "omush/database/idatabaseobject.h"
#include "omush/database/database.h"
#include "omush/library/uuid.h"

namespace omush {
  bool hasFlag(std::shared_ptr<IDatabase> &db,
               std::shared_ptr<IDatabaseObject> &object,
               std::string name);

  class DatabaseObject : public IDatabaseObject {
    friend class DatabaseObjectDefinition;
    friend class DatabaseFactory;
   public:
    DatabaseObject() {}
    virtual std::string getName() const override;
    virtual library::uuid getUuid() const override;
    virtual DatabaseObjectType getType() const override;
    virtual void setName(std::string name) override;
    virtual void setLocation(std::shared_ptr<IDatabaseObject> location)
      override;
    virtual void addContent(std::shared_ptr<IDatabaseObject> content)
      override;
    virtual void getLocation(std::shared_ptr<IDatabaseObject> &location)
      override;
    virtual void getOwner(std::shared_ptr<IDatabaseObject> &owner)
      override;
    virtual void getContents(std::vector<std::shared_ptr<IDatabaseObject>> &contents) override;
    virtual bool hasFlagByBit(uint64_t bit) const override;
    virtual void addFlagByBit(uint64_t bit) override;
    virtual void removeFlagByBit(uint64_t bit) override;
    virtual bool getAttribute(std::string attribute, std::string &str) override;
   protected:
    uint64_t flags_;
    std::string name_;
    DatabaseObjectType type_;
    library::uuid uuid_;
    std::shared_ptr<IDatabaseObject> location_;
    std::shared_ptr<IDatabaseObject> owner_;
    std::map<library::uuid,std::shared_ptr<IDatabaseObject>> contents_;
  };



}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECT_H_
