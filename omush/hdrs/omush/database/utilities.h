/**
 * \file utilities.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_UTILITIES_H_
#define OMUSH_HDRS_OMUSH_DATABASE_UTILITIES_H_

#include <memory>
#include "omush/database/idatabase.h"
#include "omush/database/databaseobject.h"


namespace omush {

  bool hasFlag(std::shared_ptr<IDatabase> db,
               std::shared_ptr<IDatabaseObject> object,
               std::string name) {
    Flag* f = db->flags.getFlag(name);
    if (f == NULL) {
      return false;
    }

    return object->hasFlagByBit(f->bit);
  }

  bool hasFlagByBit(std::shared_ptr<IDatabaseObject> object,
                    uint64_t bit) {
    return object->hasFlagByBit(bit);
  }

  void addFlag(std::shared_ptr<IDatabase> db,
               std::shared_ptr<IDatabaseObject> object,
               std::string name) {
    Flag* f = db->flags.getFlag(name);
    if (f == NULL) {
      return;
    }

    return object->addFlagByBit(f->bit);
  }

  void addFlagByBit(std::shared_ptr<IDatabaseObject> object,
                    uint64_t bit) {
    return object->addFlagByBit(bit);
  }

  void removeFlagByBit(std::shared_ptr<IDatabaseObject> object,
                       uint64_t bit) {
    return object->removeFlagByBit(bit);
  }

  void removeFlag(std::shared_ptr<IDatabase> db,
                  std::shared_ptr<IDatabaseObject> object,
                  std::string name) {
    Flag* f = db->flags.getFlag(name);
    if (f == NULL) {
      return;
    }

    return object->removeFlagByBit(f->bit);
  }

  bool hasOwnershipOfObject(std::shared_ptr<IDatabaseObject> caller,
                            std::shared_ptr<IDatabaseObject> target) {
    if (caller == target)
      return true;

    std::shared_ptr<IDatabaseObject> owner;
    target->getOwner(owner);
    if (owner == caller)
      return true;

    return false;
  }

}  // namespace omush


#endif  // OMUSH_HDRS_OMUSH_DATABASE_UTILITIES_H_
