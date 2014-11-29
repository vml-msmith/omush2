/**
 * \file databasestorage.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASESTORAGE_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASESTORAGE_H_

#include <string>
#include "omush/database/idatabase.h"

namespace omush {
  class DatabaseStorage {
   public:
    DatabaseStorage();
    bool loadFromDatabase(std::string databaseName,
                          std::shared_ptr<IDatabase> dptr);
    bool saveToDatabase(std::string databaseName,
                        std::shared_ptr<IDatabase> dptr);
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASESTORAGE_H_
