/**
 * \file databasematcher.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASEMATCHER_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASEMATCHER_H_

#include <string>
#include <vector>
#include "omush/database/idatabase.h"
#include "omush/database/playerobject.h"

namespace omush {

#define SEARCH_LOCATION   0x10U
#define SEARCH_INVENTORY  0x20U
#define SEARCH_SELF       0x40U
#define SEARCH_REMOTE     0x80U
  class DatabaseMatcherOptions {
   public:

  };

  class DatabaseMatcher {
   public:
    typedef std::vector<std::shared_ptr<IDatabaseObject>> DBMatchList;

    DatabaseMatcher(const std::shared_ptr<IDatabase> &db,
                    const std::shared_ptr<IDatabaseObject> &looker);
    static bool findPlayer(IDatabase *db,
                           std::string lookupString,
                           std::shared_ptr<IDatabaseObject> &object);
    static bool findTargets(IDatabase *db,
                            std::shared_ptr<IDatabaseObject> &looker,
                            std::string lookupString,
                            std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects);
   private:
    std::shared_ptr<IDatabase> database_;
    std::shared_ptr<IDatabaseObject> looker_;
    uint64_t searchFlags_;

  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASEMATCHER_H_
