/**
 * \file databasestorage.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASESTORAGE_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASESTORAGE_H_

#include <string>
#include "omush/database/idatabase.h"

// TODO(msmith): Get rid of this from the header if we can.
#include "SQLiteCpp/SQLiteCpp.h"

namespace omush {
  class DatabaseStorage {
   public:
    DatabaseStorage();
    bool loadFromDatabase(std::string databaseName,
                          std::shared_ptr<IDatabase> dptr);
    bool saveToDatabase(std::string databaseName,
                        std::shared_ptr<IDatabase> dptr);
   private:
    void dropTables_(SQLite::Database &db) const;
    void createTables_(SQLite::Database &db) const;
    void populateFlagTable_(SQLite::Database &db,
                              std::shared_ptr<IDatabase> dptr) const;
    void populatePowerTable_(SQLite::Database &db,
                               std::shared_ptr<IDatabase> dptr) const;
    void populateObjectTable_(SQLite::Database &db,
                                std::shared_ptr<IDatabase> dptr) const;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASESTORAGE_H_
