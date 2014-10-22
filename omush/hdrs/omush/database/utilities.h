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
               std::string name);

  bool hasFlagByBit(std::shared_ptr<IDatabaseObject> object,
                    uint64_t bit);

  void addFlag(std::shared_ptr<IDatabase> db,
               std::shared_ptr<IDatabaseObject> object,
               std::string name);

  void addFlagByBit(std::shared_ptr<IDatabaseObject> object,
                    uint64_t bit);

  void removeFlagByBit(std::shared_ptr<IDatabaseObject> object,
                       uint64_t bit);

  void removeFlag(std::shared_ptr<IDatabase> db,
                  std::shared_ptr<IDatabaseObject> object,
                  std::string name);

  bool hasPower(std::shared_ptr<IDatabase> db,
                std::shared_ptr<IDatabaseObject> object,
                std::string name,
                int level);

  bool hasPower(std::shared_ptr<IDatabase> db,
                std::shared_ptr<IDatabaseObject> object,
                std::string name);

  bool hasPowerByBit(std::shared_ptr<IDatabase> db,
                     std::shared_ptr<IDatabaseObject> object,
                     uint64_t bit,
                     int level);

  void addPower(std::shared_ptr<IDatabase> db,
                std::shared_ptr<IDatabaseObject> object,
                std::string name,
                int level);

  void addPower(std::shared_ptr<IDatabase> db,
                std::shared_ptr<IDatabaseObject> object,
                std::string name);

  void addPowerByBit(std::shared_ptr<IDatabaseObject> object,
                     uint64_t bit,
                     int level);

  void addPowerByBit(std::shared_ptr<IDatabaseObject> object,
                     uint64_t bit);

  void removePowerByBit(std::shared_ptr<IDatabaseObject> object,
                        uint64_t bit);

  void removePower(std::shared_ptr<IDatabase> db,
                   std::shared_ptr<IDatabaseObject> object,
                   std::string name);

  bool hasOwnershipOfObject(std::shared_ptr<IDatabaseObject> caller,
                            std::shared_ptr<IDatabaseObject> target);

  bool hasPowerOver(std::shared_ptr<IDatabase> db,
                    std::shared_ptr<IDatabaseObject> object,
                    std::shared_ptr<IDatabaseObject> object2,
                    std::string name);

  bool isRootUser(std::shared_ptr<IDatabase> db,
                  std::shared_ptr<IDatabaseObject> object);
}  // namespace omush


#endif  // OMUSH_HDRS_OMUSH_DATABASE_UTILITIES_H_
