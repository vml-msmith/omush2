/**
 * \file utilities.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/utilities.h"
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


  bool hasPower(std::shared_ptr<IDatabase> db,
                std::shared_ptr<IDatabaseObject> object,
                std::string name,
                int level) {
    /*
    if (db.root() == object)
      return true;
    */

    Power* p = db->powers.getPower(name);
    if (p == NULL) {
      return false;
    }

    return object->hasPowerByBit(p->bit, level);
  }


  bool hasPower(std::shared_ptr<IDatabase> db,
                std::shared_ptr<IDatabaseObject> object,
                std::string name) {
    return hasPower(db, object, name, 0);
  }

  bool hasPowerByBit(std::shared_ptr<IDatabase> db,
                     std::shared_ptr<IDatabaseObject> object,
                     uint64_t bit,
                     int level) {
    /*
    if (db.root() == object)
      return true;
    */

    return object->hasPowerByBit(bit, level);
  }

  void addPower(std::shared_ptr<IDatabase> db,
                std::shared_ptr<IDatabaseObject> object,
                std::string name,
                int level) {
    Power* p = db->powers.getPower(name);
    if (p == NULL) {
      return;
    }

    return object->addPowerByBit(p->bit, level);
  }

  void addPower(std::shared_ptr<IDatabase> db,
                std::shared_ptr<IDatabaseObject> object,
                std::string name) {
    return addPower(db, object, name, 0);
  }

  void addPowerByBit(std::shared_ptr<IDatabaseObject> object,
                     uint64_t bit,
                     int level) {
    return object->addPowerByBit(bit, level);
  }

  void addPowerByBit(std::shared_ptr<IDatabaseObject> object,
                     uint64_t bit) {
    return addPowerByBit(object, bit, 0);
  }

  void removePowerByBit(std::shared_ptr<IDatabaseObject> object,
                        uint64_t bit) {
    return object->removePowerByBit(bit);
  }

  void removePower(std::shared_ptr<IDatabase> db,
                   std::shared_ptr<IDatabaseObject> object,
                   std::string name) {
    Power* p = db->powers.getPower(name);
    if (p == NULL) {
      return;
    }

    return object->removePowerByBit(p->bit);
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

  bool hasPowerOver(std::shared_ptr<IDatabase> db,
                    std::shared_ptr<IDatabaseObject> object,
                    std::shared_ptr<IDatabaseObject> object2,
                    std::string name) {
    return true;
  }
}  // namespace omush
