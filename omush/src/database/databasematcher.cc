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
#include <iostream>

namespace omush {
  DatabaseMatcher::DatabaseMatcher(const std::shared_ptr<IDatabase> &db,
                                   const std::shared_ptr<IDatabaseObject> &looker)
    : database_(db), looker_(looker) {
      searchFlags_ =
      DatabaseMatcherFlag::Location |
      DatabaseMatcherFlag::Inventory |
      DatabaseMatcherFlag::Self |
      DatabaseMatcherFlag::Remote;

      typeFlags_ =
      DatabaseMatcherTypeFlag::Room |
      DatabaseMatcherTypeFlag::Player |
      DatabaseMatcherTypeFlag::Exit |
      DatabaseMatcherTypeFlag::Thing;

  }

  bool DatabaseMatcher::flagIsSet_(uint64_t flag) {
    return (searchFlags_ & flag) == flag;
  }
  bool DatabaseMatcher::typeIsSet_(uint64_t flag) {
    return (searchFlags_ & flag) == flag;
  }

  bool DatabaseMatcher::matchHere_(std::string lookupString,
                                   std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects) {
    if (library::string::iequals(lookupString, "here") && 
        flagIsSet_(DatabaseMatcherFlag::Location)) {
      // TODO(msmith) Match type of loc to typeflag. 
      std::shared_ptr<IDatabaseObject> loc;
      looker_->getLocation(loc);
      
      //      if (typeIsSet_(loc->getType())) {
      objects->push_back(loc);
      return true;
      //}
    }
 
    return false;
  }

  bool DatabaseMatcher::matchMe_(std::string lookupString,
                                 std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects) {
    if (library::string::iequals(lookupString, "me") &&
        flagIsSet_(DatabaseMatcherFlag::Self)) {
      // TODO(msmith): Match tpye of me to type flag.
      objects->push_back(looker_);
      return true;
    }

    return false;
  }

  bool DatabaseMatcher::matchDbref_(std::string lookupString,
                                    std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects) {
    if (library::string::iequals(lookupString.substr(0,1), "#")) {
      std::string theRest = lookupString.substr(1,lookupString.length());
      Dbref ref = atoi(theRest.c_str());
      
      std::shared_ptr<IDatabaseObject> object;
      
      if (database_->getObjectByDbref(ref, object)) {
        // TODO(msmith): Match the type flag and remote (if the loc is remote).
        objects->push_back(object);
        return true;
      }
      
      return false;
    }

    
    return false;
  }

  
  bool DatabaseMatcher::matchPlayer_(std::string lookupString,
                                     std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects) {
    if (library::string::iequals(lookupString.substr(0,1), "*") &&
        typeIsSet_(DatabaseMatcherTypeFlag::Player)) {
      // Find by absolute name.
      
    }
    
    return false;
  }

  void getLocationTargets_(std::map<library::uuid, std::shared_ptr<IDatabaseObject>>& objects) {
    if (!flagIsSet_(DatabaseMatcherFlag::Location)) {
      return;
    }

    std::shared_ptr<IDatabaseObject> location = nullptr;
    looker_->getLocation(location);
    
    if (location == nullptr) {
      return;
    }
    
    std::vector<std::shared_ptr<IDatabaseObject>> contents;    
    objects[location->getUuid()] = location;

    // Get location contents.
    location->getContents(contents);
    for (auto item : contents) {
      listeners[item->getUuid()] = item;
    }
  }
  
  bool DatabaseMatcher::find(std::string lookupString,
                             std::shared_ptr<std::vector<std::shared_ptr<IDatabaseObject>>>& objects) {
 
    if (matchHere_(lookupString, objects))
      return true;
    
    if (matchMe_(lookupString, objects))
      return true;
    
    if (matchDbref_(lookupString, objects))
      return true;

    if (matchPlayer_(lookupString, objects))
      return true;
         

    std::map<library::uuid, std::shared_ptr<IDatabaseObject>> possibleTargets;
    getLocationTargets_(possibleTargets);
    
    
    // Get the room, add it to the listeners.
    bool searchPartial = true;
    std::shared_ptr<IDatabaseObject> location = nullptr;
    looker_->getLocation(location);
    std::vector<std::shared_ptr<IDatabaseObject>> contents;

    if (location != nullptr) {
      listeners[location->getUuid()] = location;
      
      // Get location contents.
      location->getContents(contents);
      for (auto item : contents) {
        listeners[item->getUuid()] = item;
      }
      
      // TODO(msmith): Notifiy exits that are "open".
    }
    
    looker_->getContents(contents);
    for (auto item : contents) {
      std::cout << item->getName() << std::endl;
      listeners[item->getUuid()] = item;
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
    std::cout << "Find " << lookupString << std::endl;
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

    if (library::string::iequals(lookupString.substr(0,1), "#")) {
      std::string theRest = lookupString.substr(1,lookupString.length());
      Dbref ref = atoi(theRest.c_str());

      std::shared_ptr<IDatabaseObject> object;
      if (db->getObjectByDbref(ref, object)) {
        objects->push_back(object);
        return true;
      }

      return false;
    }

    //    return false;
    // Search *playerName.

    // Get the room, add it to the listeners.
    bool searchPartial = true;
    std::map<library::uuid, std::shared_ptr<IDatabaseObject>> listeners;
    std::shared_ptr<IDatabaseObject> location = nullptr;
    looker->getLocation(location);
    std::vector<std::shared_ptr<IDatabaseObject>> contents;
    if (location != nullptr) {
      listeners[location->getUuid()] = location;

      // Get location contents.
      location->getContents(contents);
      for (auto item : contents) {
        listeners[item->getUuid()] = item;
      }

      // TODO(msmith): Notifiy exits that are "open".
    }

    looker->getContents(contents);
    for (auto item : contents) {
      std::cout << item->getName() << std::endl;
      listeners[item->getUuid()] = item;
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
