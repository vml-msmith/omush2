/**
 * \file databaseobject.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECT_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECT_H_

#include "omush/database/idatabaseobject.h"
#include <memory>
#include "omush/database/database.h"

namespace omush {

  class DatabaseObject : public IDatabaseObject {
    friend class DatabaseObjectDefinition;
   public:
    DatabaseObject() {};
    virtual std::string getName() override;

   protected:
    std::string name_;
    DatabaseObjectType type_;
   private:

  };

  class DatabaseObjectDefinition {
   public:
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) {
    }

    virtual bool factory(std::shared_ptr<DatabaseObject> &object) {
      object = std::shared_ptr<DatabaseObject>(new DatabaseObject());
      return true;
    }
   protected:
    void setType(std::shared_ptr<DatabaseObject> &object, DatabaseObjectType type) {
      object->type_ = type;
    }
    DatabaseObjectDefinition() {
    }

  };

  class DatabaseObjectDefinitionPlayer : public DatabaseObjectDefinition {
  public:
    DatabaseObjectDefinitionPlayer() {
    }
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) override {
      DatabaseObjectDefinition::postSetup(object);
      DatabaseObjectDefinition::setType(object, PLAYER);
    }
  };

  class DatabaseObjectDefinitionRoom : public DatabaseObjectDefinition {
  public:
    DatabaseObjectDefinitionRoom() {
    }
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) override {
      DatabaseObjectDefinition::postSetup(object);
      DatabaseObjectDefinition::setType(object, ROOM);
    }
  };


  class DatabaseFactory {
   public:
    bool buildObject(DatabaseObjectDefinition definition,
                     std::shared_ptr<DatabaseObject>& newObject) {
      if (definition.factory(newObject)) {
        // TODO(msmith): Log an error.
        return false;
      }
      definition.postSetup(newObject);

      return true;
    }
  };

}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECT_H_
