/**
 * \file databaseobject.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECT_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECT_H_

#include <memory>
#include <string>
#include <vector>

#include "omush/database/idatabaseobject.h"
#include "omush/database/database.h"
#include "omush/library/uuid.h"

namespace omush {
  bool hasFlag(const std::shared_ptr<IDatabase> &db,
               const std::shared_ptr<IDatabaseObject> &object,
               std::string name);

  class DatabaseObject : public IDatabaseObject {
    friend class DatabaseObjectDefinition;
    friend class DatabaseFactory;
   public:
    DatabaseObject() : dbref_(0), home_(nullptr) {
      for (int i = 0; i <= 5; ++i)
        powers_.push_back(0);
    }
    virtual std::string getName() const override;
    virtual Dbref getDbref() const override;
    virtual void setDbref(Dbref dbref) override;
    virtual library::uuid getUuid() const override;
    virtual DatabaseObjectType getType() const override;
    virtual void setName(std::string name) override;
    virtual void setLocation(std::shared_ptr<IDatabaseObject> location)
      override;
    virtual void addContent(std::shared_ptr<IDatabaseObject> content)
      override;
    virtual void removeContent(std::shared_ptr<IDatabaseObject> content) override;
    virtual void getLocation(std::shared_ptr<IDatabaseObject> &location)
      override;
    virtual void getOwner(std::shared_ptr<IDatabaseObject> &owner)
      override;
    virtual void setOwner(std::shared_ptr<IDatabaseObject> owner) override;
    virtual void getHome(std::shared_ptr<IDatabaseObject> &home)
      override;
    virtual void setHome(std::shared_ptr<IDatabaseObject> home) override;
    virtual void getContents(std::vector<std::shared_ptr<IDatabaseObject>> &contents) override;
    virtual void getFlagMask(uint64_t &bit) const override;
    virtual void setFlagMask(uint64_t maks) override;
    virtual bool hasFlagByBit(uint64_t bit) const override;
    virtual void addFlagByBit(uint64_t bit) override;
    virtual void removeFlagByBit(uint64_t bit) override;
    virtual bool hasPowerByBit(uint64_t bit, int level) const override;
    virtual bool hasPowerByBit(uint64_t bit) const override;
    virtual void addPowerByBit(uint64_t bit, int level) override;
    virtual void addPowerByBit(uint64_t bit) override;
    virtual void removePowerByBit(uint64_t bit) override;
    virtual void getPowerListAsString(std::string &list) const override;
    virtual bool getAttribute(std::string attribute, std::string &str) override;
    virtual void setAttribute(std::string attributeName, std::string attributeValue) override;
    virtual void getAttributeList(std::vector<std::string> &list) override;
    virtual void setPowerMaskAtLevel(uint64_t bit, int level) override;
   protected:
    uint64_t flags_;
    std::vector<uint64_t> powers_;
    std::string name_;
    DatabaseObjectType type_;
    library::uuid uuid_;
    std::shared_ptr<IDatabaseObject> location_;
    std::shared_ptr<IDatabaseObject> owner_;
    std::shared_ptr<IDatabaseObject> home_;
    std::map<library::uuid,std::shared_ptr<IDatabaseObject>> contents_;
    std::map<std::string,std::string> attributes_;
    Dbref dbref_;
  };



}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECT_H_
