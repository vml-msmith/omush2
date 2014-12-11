/**
 * \file databaseobject.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/databaseobject.h"
#include <string>
#include "omush/library/uuid.h"

namespace omush {
  std::string DatabaseObject::getName() const {
    return name_;
  }

  void DatabaseObject::setName(std::string name) {
    name_ = name;
  }

  Dbref DatabaseObject::getDbref() const  {
    return dbref_;
  }

  void DatabaseObject::setDbref(Dbref dbref) {
    dbref_ = dbref;
  }

  library::uuid DatabaseObject::getUuid() const {
    return uuid_;
  }

  DatabaseObjectType DatabaseObject::getType() const {
    return type_;
  }

  void DatabaseObject::setLocation(
      std::shared_ptr<IDatabaseObject> location) {
    if (location == nullptr)
      return;

    location_ = location;
  }

  void DatabaseObject::addContent(
      std::shared_ptr<IDatabaseObject> content) {
    if (contents_.find(content->getUuid()) != contents_.end()) {
      return;
    }

    contents_[content->getUuid()] = content;
  }

  void DatabaseObject::removeContent(
      std::shared_ptr<IDatabaseObject> content) {
    if (contents_.find(content->getUuid()) == contents_.end()) {
      return;
    }

    contents_.erase(content->getUuid());
  }

  void DatabaseObject::getLocation(
      std::shared_ptr<IDatabaseObject> &location) {
    if (location_ == nullptr) {
      return;
    }

    location = location_;
  }

  void DatabaseObject::setOwner(std::shared_ptr<IDatabaseObject> owner)  {
    owner_ = owner;
  }

  void DatabaseObject::getOwner(
      std::shared_ptr<IDatabaseObject> &owner) {
    if (owner_ == nullptr) {
      return;
    }

    owner = owner_;
  }

  void DatabaseObject::setHome(std::shared_ptr<IDatabaseObject> home)  {
    home_ = home;
  }

  void DatabaseObject::getHome(
      std::shared_ptr<IDatabaseObject> &home) {
    if (home_ == nullptr) {
      return;
    }

    home = home_;
  }

  void DatabaseObject::getContents(
      std::vector<std::shared_ptr<IDatabaseObject>> &contents) {
                                   printf("Get content\n");
    for (auto &item : contents_) {
      contents.push_back(item.second);
    }
  }

  bool DatabaseObject::hasFlagByBit(uint64_t bit) const {
    return (flags_ & bit) == bit;
  }

  void DatabaseObject::getFlagMask(uint64_t &bit) const {
    bit = flags_;
  }

  void DatabaseObject::setFlagMask(uint64_t mask) {
    flags_ = mask;
  }

  void DatabaseObject::addFlagByBit(uint64_t bit) {
    flags_ = (flags_ | bit);
  }

  void DatabaseObject::removeFlagByBit(uint64_t bit) {
    if (hasFlagByBit(bit)) {
        flags_ = (flags_ ^ bit);
    }
  }
  bool DatabaseObject::hasPowerByBit(uint64_t bit) const {
    return hasPowerByBit(bit, 0);
  }

  bool DatabaseObject::hasPowerByBit(uint64_t bit, int level) const {
    // TODO(msmith): Make these constants or something.
    if (level < 0 || level > 5) {
      return false;
    }

    return (powers_[level] & bit) == bit;
  }

  void DatabaseObject::addPowerByBit(uint64_t bit) {
    return addPowerByBit(bit, 0);
  }

  void DatabaseObject::addPowerByBit(uint64_t bit, int level) {
    // TODO(msmith): Make these constants or something.
    if (level < 0 || level > 5) {
      return;
    }

    removePowerByBit(bit);

    powers_[level] = (powers_[level] | bit);
    if (level != 0) {
      powers_[0] = (powers_[0] | bit);
    }
  }

  void DatabaseObject::removePowerByBit(uint64_t bit) {
    for (int level = 0; level <= 5; ++level) {
      if (hasPowerByBit(bit, level)) {
        powers_[level] = (powers_[level] ^ bit);
      }
    }
  }

  void DatabaseObject::getPowerListAsString(std::string &list) const {
    list = "";
    for (int level = 0; level <= 5; ++level) {
      list += std::to_string(level) + ":" + std::to_string(powers_[level]) + " ";
    }
  }

  void DatabaseObject::setPowerMaskAtLevel(uint64_t bit, int level)  {
    powers_[level] = bit;
  }

  bool DatabaseObject::getAttribute(std::string attribute,
                                    std::string &str) {
    if (attributes_.find(attribute) == attributes_.end()) {
      return false;
    }


    str = attributes_[attribute];
    return true;
  }

  void DatabaseObject::getAttributeList(std::vector<std::string> &list) {
    for (auto &iter : attributes_) {
      list.push_back(iter.first);
    }
  }

  void DatabaseObject::setAttribute(std::string attributeName,
                                    std::string attributeValue)  {
    if (attributes_.find(attributeName) == attributes_.end()) {
      attributes_[attributeName] = attributeValue;
      return;
    }

    attributes_.insert(
        std::pair<std::string,std::string>(attributeName,
                                           attributeValue));
  }
}  // namespace omush
