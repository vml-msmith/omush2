/**
 * \file databasestorage.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/database/databasestorage.h"
#include "omush/database/idatabase.h"
#include "omush/database/idatabaseobject.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include <iostream>
#include <map>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "omush/database/databasefactory.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionplayer.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionroom.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionthing.h"
#include "omush/database/objectdefinitions/databaseobjectdefinitionexit.h"
#include "omush/library/string.h"

namespace omush {
  DatabaseStorage::DatabaseStorage() {}
  bool DatabaseStorage::loadFromDatabase(std::string databaseName,
                                         std::shared_ptr<IDatabase> dptr) {
    //return false;
    try {
      SQLite::Database db(databaseName,
                          SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);

      SQLite::Statement   flagQuery(db, "SELECT * FROM flags");
      while (flagQuery.executeStep()) {
        int bit             = flagQuery.getColumn(0);
        const char* name    = flagQuery.getColumn(1);
        const char* alias   = flagQuery.getColumn(2);
        const char* letter  = flagQuery.getColumn(3);
        dptr->flags.addFlagWithBit(Flag(name, letter[0]), bit);
      }

      SQLite::Statement powerQuery(db, "SELECT * FROM powers");
      while (powerQuery.executeStep()) {
        int bit                  = powerQuery.getColumn(0);
        const char* name         = powerQuery.getColumn(1);
        const char* alias        = powerQuery.getColumn(2);
        const char* description  = powerQuery.getColumn(3);
        int isTiered             = powerQuery.getColumn(4);

        dptr->powers.addWithBit(Power(name,
                                      description,
                                      (isTiered == 1)),
                                bit);
      }


      DatabaseFactory factory;
      SQLite::Statement objectQuery(db, "SELECT * FROM objects");
      while (objectQuery.executeStep()) {
        std::shared_ptr<DatabaseObject> dbObject;
        std::string id      = objectQuery.getColumn(0);
        int dbref           = objectQuery.getColumn(1);
        const char* name    = objectQuery.getColumn(2);
        int type            = objectQuery.getColumn(3);
        int flags           = objectQuery.getColumn(4);
        const char* powersList  = objectQuery.getColumn(5);

        // Switch the type.
        DatabaseObjectDefinition* definition;
        switch (type) {
        case PLAYER:
          factory.buildObject(DatabaseObjectDefinitionPlayer::getInstance(),
                              dbObject);
          break;
        case ROOM:
          factory.buildObject(DatabaseObjectDefinitionRoom::getInstance(),
                              dbObject);
          break;
        case EXIT:
          factory.buildObject(DatabaseObjectDefinitionExit::getInstance(),
                              dbObject);
          break;
        default:
          factory.buildObject(DatabaseObjectDefinitionThing::getInstance(),
                              dbObject);
        }
        factory.setUuid(boost::lexical_cast<library::uuid>(id),
                        dbObject);

        dbObject->setDbref(dbref);
        dbObject->setName(name);
        dbObject->setFlagMask(flags);

        std::vector<std::string> powers = library::string::splitIntoSegments(std::string(powersList),
                                                                             " ");

        for (auto iter : powers) {
          std::vector<std::string> bits = library::string::splitIntoSegments(iter, ":");
          dbObject->setPowerMaskAtLevel(atoi(bits[1].c_str()), atoi(bits[0].c_str()));
        }
        dptr->addObject(dbObject);
        // Need to add the powers & flags.
      }

      SQLite::Statement propertyQuery(db, "SELECT * FROM properties");
      while (propertyQuery.executeStep()) {
        std::string id      = propertyQuery.getColumn(0);
        const char* name    = propertyQuery.getColumn(1);
        const char* value   = propertyQuery.getColumn(2);
        std::shared_ptr<IDatabaseObject> dbObject;
        dptr->getObjectByUUID(boost::lexical_cast<library::uuid>(id),
                              dbObject);

        if (dbObject) {
          if (library::string::iequals(std::string(name), "location")) {
            std::shared_ptr<IDatabaseObject> targetObject;
            dptr->getObjectByUUID(boost::lexical_cast<library::uuid>(value),
                                  targetObject);
            if (targetObject) {
              targetObject->addContent(dbObject);
              dbObject->setLocation(targetObject);
            }
          }
          else if (library::string::iequals(std::string(name), "owner")) {
            std::shared_ptr<IDatabaseObject> targetObject;
            dptr->getObjectByUUID(boost::lexical_cast<library::uuid>(value),
                                  targetObject);
            if (targetObject) {
              //              dbObject->setOwner(targetObject);
            }
          }
        }
      }

      SQLite::Statement attributeQuery(db, "SELECT * FROM attributes");
      while (attributeQuery.executeStep()) {
        std::string id      = attributeQuery.getColumn(0);
        const char* name    = attributeQuery.getColumn(1);
        const char* value   = attributeQuery.getColumn(2);

        std::shared_ptr<IDatabaseObject> dbObject;
        dptr->getObjectByUUID(boost::lexical_cast<library::uuid>(id),
                              dbObject);

        if (dbObject) {
          dbObject->setAttribute(name, value);
        }
      }

      return true;
    }
    catch (std::exception& e) {
      std::cout << "exception: " << e.what() << std::endl;
      return false;
    }
  }

  void DatabaseStorage::dropTables_(SQLite::Database &db) const {
    db.exec("DROP TABLE IF EXISTS flags");
    db.exec("DROP TABLE IF EXISTS powers");
    db.exec("DROP TABLE IF EXISTS objects");
    db.exec("DROP TABLE IF EXISTS properties");
    db.exec("DROP TABLE IF EXISTS attributes");
  }

  void DatabaseStorage::createTables_(SQLite::Database &db) const {
    db.exec("CREATE TABLE flags ("       \
            "id INTEGER PRIMARY KEY, "   \
            "name TEXT, "                \
            "alias TEXT, "               \
            "letter TEXT"                \
            ")");

    db.exec("CREATE TABLE powers ("      \
            "id INTEGER PRIMARY KEY, "   \
            "name TEXT, "                \
            "alias TEXT, "               \
            "description TEXT, "         \
            "isTiered INTEGER"           \
            ")");

    db.exec("CREATE TABLE objects ("  \
            "id text PRIMARY KEY, "   \
            "dbref INTEGER, "         \
            "name TEXT, "             \
            "type INTEGER, "          \
            "flags INTEGER, "         \
            "powers TEXT "            \
            ")");

    db.exec("CREATE TABLE properties ("         \
            "id text, "                         \
            "name TEXT, "                       \
            "value TEXT"                        \
            ")");

    db.exec("CREATE TABLE attributes ("         \
            "id text, "                         \
            "name TEXT, "                       \
            "value TEXT"                        \
            ")");
  }

  void DatabaseStorage::populateFlagTable_(SQLite::Database &db,
                                           std::shared_ptr<IDatabase> dptr) const {
    for (auto &iter : dptr->flags.getAllFlags()) {
      std::string alias = "";
      std::string stmt = "INSERT INTO flags VALUES (" +
        std::to_string(iter.second.bit) + ", " +
        "\"" + iter.second.name + "\", " +
        "\"" + "bleh" + "\", " +
        "\"" + iter.second.letter + "\"" +
        ")";
      int nb = db.exec(stmt);
    }
  }

  void DatabaseStorage::populatePowerTable_(SQLite::Database &db,
                                            std::shared_ptr<IDatabase> dptr) const {

      for (auto &iter : dptr->powers.getAllPowers()) {
        std::string alias = "";
        std::string stmt = "INSERT INTO powers VALUES (" +
          std::to_string(iter.second.bit) + ", " +
          "\"" + iter.second.name + "\", " +
          "\"" + "bleh" + "\", " +
          "\"" + iter.second.description + "\", " +
          std::to_string(iter.second.isTiered) +
          ")";
        int nb = db.exec(stmt);
      }

  }
  void DatabaseStorage::populateObjectTable_(SQLite::Database &db,
                                             std::shared_ptr<IDatabase> dptr) const {
    std::map<library::uuid, std::shared_ptr<IDatabaseObject>> map;
    dptr->getObjects(&map);
    for (auto &iter : map) {
      std::string uuid = boost::lexical_cast<std::string>(iter.first);
      int type = iter.second->getType();
      std::string name = iter.second->getName();
      uint64_t flagMask;;
      iter.second->getFlagMask(flagMask);
      std::string flags = std::to_string(flagMask);
      std::string powers;
      iter.second->getPowerListAsString(powers);

      std::string stmt = "INSERT INTO objects VALUES (\"" +
        uuid + "\", " +
        std::to_string(iter.second->getDbref()) + ", " +
        "\"" + name + "\", " +
        std::to_string(type)  + ", " +
        flags + ", " +
        "\"" + powers + "\" " +
        ")";

      int nb = db.exec(stmt);

      std::map<std::string,std::string> properties;


      std::shared_ptr<IDatabaseObject> loc;
      iter.second->getLocation(loc);
      std::shared_ptr<IDatabaseObject> owner;

      iter.second->getOwner(owner);

      if (loc) {
        properties.insert(std::pair<std::string,std::string>("location",
                                                             boost::lexical_cast<std::string>(loc->getUuid())));
      }
      if (owner) {
        properties.insert(std::pair<std::string,std::string>("owner",
                                                             boost::lexical_cast<std::string>(owner->getUuid())));
      }

      for (auto &prop : properties) {
        stmt = "INSERT INTO properties VALUES(\"" +
          uuid + "\", " +
          "\"" + prop.first + "\", " +
          "\"" + prop.second + "\" " +
          ")";

        int nb = db.exec(stmt);
      }

      std::vector<std::string> attributes;
      iter.second->getAttributeList(attributes);
      for (auto attributeName : attributes) {
        std::string value;
        iter.second->getAttribute(attributeName, value);
        stmt = "INSERT INTO attributes VALUES(\"" +
          uuid + "\", " +
          "\"" + attributeName + "\", " +
          "\"" + value + "\" " +
          ")";
        int nb = db.exec(stmt);
      }
    }
  }

  bool DatabaseStorage::saveToDatabase(std::string databaseName,
                                       std::shared_ptr<IDatabase> dptr) {
    try {
      SQLite::Database db(databaseName,
                          SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
      dropTables_(db);

      SQLite::Transaction transaction(db);

      createTables_(db);
      populateFlagTable_(db, dptr);
      populatePowerTable_(db, dptr);
      populateObjectTable_(db, dptr);


      transaction.commit();
      return true;
    }
    catch (std::exception& e) {
      std::cout << "exception: " << e.what() << std::endl;
      return false;
    }
  }
}  // namespace omush
