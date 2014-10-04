/**
 * \file databasematcher.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/databasematcher.h"
#include <map>
#include "omush/library/string.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"

namespace omush {
  DatabaseMatcher::DatabaseMatcher(const std::shared_ptr<IDatabase> &db,
                                   const std::shared_ptr<IDatabaseObject> &looker)
    : database_(db), looker_(looker) {
      searchFlags_ =
        SEARCH_LOCATION |
        SEARCH_INVENTORY |
        SEARCH_SELF |
        SEARCH_REMOTE;
  }
  /*
  void DatabaseMatcher::type() {
  }

  void DatabaseMatcher::setSearchFlags(uint64_t searchFlags) {
  }

  bool DatabaseMatcher::match(std::string matchString,
                              std::shared_ptr<DBMatchList>) {
                              }*/



  /*
  DatabaseMatcher::DatabaseMatcher() {
  }
  */
  // TODO(msmith): Right now this only finds player based on the name
  // of the player object. In the future, it needs to look by dbref and
  // alias as well.
  bool DatabaseMatcher::findPlayer(IDatabase *db,
                                   std::string lookupString,
                                   std::shared_ptr<IDatabaseObject>& object) {

    if (db == NULL) {
      return false;
    }

    UuidToDbObjectMap map;
    db->getObjectsByType(PLAYER, &map);


    for (auto iter : map) {
      std::string name = iter.second->getName();
      if (library::string::iequals(name, lookupString)) {
        object = iter.second;
        return true;
      }
    }

    object = NULL;
    return false;
  }

  bool DatabaseMatcher::findTargets(IDatabase *db,
                                    std::shared_ptr<IDatabaseObject> &looker,
                                    std::string lookupString,
                                    std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects) {
    if (library::string::iequals(lookupString, "here")) {
      std::shared_ptr<IDatabaseObject> loc;
      looker->getLocation(loc);
      objects->push_back(loc);
      return true;
    }

    if (library::string::iequals(lookupString, "me")) {
      objects->push_back(looker);
      return true;
    }

    if (library::string::iequals(lookupString.substr(0,1),"#")) {
      // DBref.
      return false;
    }

    // Search *playerName.

    // Get the room, add it to the listeners.
    bool searchPartial = true;
    std::map<library::uuid, std::shared_ptr<IDatabaseObject>> listeners;
    std::shared_ptr<IDatabaseObject> location = nullptr;
    looker->getLocation(location);
    if (location != nullptr) {
      listeners[location->getUuid()] = location;

      // Get location contents.
      std::vector<std::shared_ptr<IDatabaseObject>> contents;
      location->getContents(contents);
      for (auto item : contents) {
        listeners[item->getUuid()] = item;
      }

      // TODO(msmith): Notifiy exits that are "open".
    }


    std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>> partial(new std::vector<std::shared_ptr<IDatabaseObject>>);
    std::string pattern = lookupString + "(.+)";
    std::regex rx(pattern.c_str(), std::regex::icase);
    for (auto& item : listeners) {
      if (library::string::iequals(item.second->getName(), lookupString)) {
        objects->push_back(item.second);
        searchPartial = false;
      }
      else if (searchPartial) {
        try {
          std::cmatch what;
          if (std::regex_match(item.second->getName().c_str(), what, rx)) {
            std::cout << "Partial match" << std::endl;
            partial->push_back(item.second);
          }
        } catch (std::regex_error &e) {
          library::log(std::string(e.what()) +
                       " " +
                       library::parseRegexErrorCode(e.code()));
        }

      }
    }

    if (!objects->empty()) {
      return true;
    }

    objects = partial;
    if (!objects->empty()) {
      return true;
    }

    return false;
  }
}  // namespace omush
