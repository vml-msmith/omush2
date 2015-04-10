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
  
#define SEARCH_TYPE_ROOM 0x10U
#define SEARCH_TYPE_PLAYER 0x20U
#define SEARCH_TYPE_EXIT 0x40U
#define SEARCH_TYPE_THING 0x80U
  enum DatabaseMatcherFlag {
    Location = 0x10,
    Inventory = 0x20,
    Self = 0x40,
    Remote = 0x80,
    Absolute = 0x020,
  };
  enum DatabaseMatcherTypeFlag {
    Room = 0x10,
    Player = 0x20,
    Exit = 0x40,
    Thing = 0x80,
  };
  
  class DatabaseMatcher {
   public:
    typedef std::vector<std::shared_ptr<IDatabaseObject>> DBMatchList;

    DatabaseMatcher(const std::shared_ptr<IDatabase> &db,
                    const std::shared_ptr<IDatabaseObject> &looker);

    bool find(std::string lookupString,
              std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects);

    static bool findPlayer(IDatabase *db,
                           std::string lookupString,
                           std::shared_ptr<IDatabaseObject> &object);

    static bool findTargets(IDatabase *db,
                            std::shared_ptr<IDatabaseObject> &looker,
                            std::string lookupString,
                            std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects);
   private:
    bool flagIsSet_(uint64_t flag);
    bool typeIsSet_(uint64_t flag);

    bool matchHere_(std::string lookupString,
                    std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects);
    bool matchMe_(std::string lookupString,
                  std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects);
    bool matchDbref_(std::string lookupString,
                     std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects);
    bool matchPlayer_(std::string lookupString,
                      std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects);
    void getLocationTargets_(std::map<library::uuid, std::shared_ptr<IDatabaseObject>>& objects);
    
    std::shared_ptr<IDatabase> database_;
    std::shared_ptr<IDatabaseObject> looker_;
    uint64_t searchFlags_;
    uint64_t typeFlags_;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASEMATCHER_H_
