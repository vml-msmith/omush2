/**
 * \file idatabaseobject.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_IDATABASEOBJECT_H_
#define OMUSH_HDRS_OMUSH_DATABASE_IDATABASEOBJECT_H_

#include <string>
#include "omush/library/uuid.h"
#include "omush/database/idatabase.h"

namespace omush {
  class IDatabaseObject {
   public:
    IDatabaseObject() {};
    virtual std::string getName() const = 0;
    virtual Dbref getDbref() const = 0;
    virtual void setDbref(Dbref dbref) = 0;
    virtual library::uuid getUuid() const = 0;
    virtual DatabaseObjectType getType() const = 0;
    virtual void setName(std::string name) = 0;
    virtual void setLocation(std::shared_ptr<IDatabaseObject> location) = 0;
    virtual void addContent(std::shared_ptr<IDatabaseObject> content) = 0;
    virtual void removeContent(std::shared_ptr<IDatabaseObject> content) = 0;
    virtual void getLocation(std::shared_ptr<IDatabaseObject> &location) = 0;
    virtual void getOwner(std::shared_ptr<IDatabaseObject> &owner) = 0;
    virtual void setOwner(std::shared_ptr<IDatabaseObject> owner) = 0;
    virtual void getHome(std::shared_ptr<IDatabaseObject> &home) = 0;
    virtual void setHome(std::shared_ptr<IDatabaseObject> home) = 0;
    virtual void getContents(std::vector<std::shared_ptr<IDatabaseObject>> &contents) = 0;
    virtual bool getAttribute(std::string attribute, std::string &str) = 0;
    virtual void setAttribute(std::string attributeName, std::string attributeValue) = 0;
    virtual void getAttributeList(std::vector<std::string> &list) = 0;
    virtual bool hasFlagByBit(uint64_t bit) const = 0;
    virtual void addFlagByBit(uint64_t bit) = 0;
    virtual void getFlagMask(uint64_t &bit) const = 0;
    virtual void setFlagMask(uint64_t mask) = 0;
    virtual void removeFlagByBit(uint64_t bit) = 0;
    virtual bool hasPowerByBit(uint64_t bit) const = 0;
    virtual bool hasPowerByBit(uint64_t bit, int level) const = 0;
    virtual void addPowerByBit(uint64_t bit) = 0;
    virtual void addPowerByBit(uint64_t bit, int level) = 0;
    virtual void removePowerByBit(uint64_t bit) = 0;
    virtual void getPowerListAsString(std::string &list) const = 0;
    virtual void setPowerMaskAtLevel(uint64_t bit, int level) = 0;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_IDATABASEOBJECT_H_
