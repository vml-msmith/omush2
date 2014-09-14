/**
 * \file databasematcher.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASEMATCHER_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASEMATCHER_H_

#include "omush/database/idatabase.h"
#include "omush/database/playerobject.h"

namespace omush {
  class DatabaseMatcher {
  public:
    DatabaseMatcher();

    static bool findPlayer(IDatabase *db,
                           std::string lookupString,
                           std::shared_ptr<IDatabaseObject> &object);
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASEMATCHER_H_
