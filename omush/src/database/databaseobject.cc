/**
 * \file databaseobject.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/databaseobject.h"
#include <string>
#include "omush/library/uuid.h"

namespace omush {
  bool hasFlag(std::shared_ptr<IDatabase> &db,
               std::shared_ptr<IDatabaseObject> &object,
               std::string name) {
    Flag* f = db->flags.getFlag(name);
    if (f == NULL) {
      return false;
    }

    return object->hasFlagByBit(f->bit);
  }

  std::string DatabaseObject::getName() const {
    return name_;
  }

  void DatabaseObject::setName(std::string name) {
    name_ = name;
  }

  library::uuid DatabaseObject::getUuid() const {
    return uuid_;
  }

  DatabaseObjectType DatabaseObject::getType() const {
    return type_;
  }

  void DatabaseObject::setLocation(std::shared_ptr<IDatabaseObject> location) {
    if (location == nullptr)
      return;

    location_ = location;

  }

  void DatabaseObject::addContent(std::shared_ptr<IDatabaseObject> content) {
    if (contents_.find(content->getUuid()) != contents_.end()) {
      return;
    }

    contents_[content->getUuid()] = content;
  }

  void DatabaseObject::getLocation(std::shared_ptr<IDatabaseObject> &location) {
    if (location_ == nullptr)
      return;
    else
      location = location_;
  }

  void DatabaseObject::getContents(std::vector<std::shared_ptr<IDatabaseObject>> &contents) {
    for (auto &item : contents_) {
      contents.push_back(item.second);
    }
  }


  bool DatabaseObject::hasFlagByBit(uint64_t bit) const {
    return (flags_ & bit) == bit;
  }

  void DatabaseObject::addFlagByBit(uint64_t bit) {
    flags_ = (flags_ | bit);
  }

  void DatabaseObject::removeFlagByBit(uint64_t bit) {
    if (hasFlagByBit(bit)) {
        flags_ = (flags_ ^ bit);
    }
  }
}  // namespace omush
