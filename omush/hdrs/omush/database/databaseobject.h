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
#include "omush/library/uuid.h"

namespace omush {

  class DatabaseObject : public IDatabaseObject {
    friend class DatabaseObjectDefinition;
    friend class DatabaseFactory;
   public:
    DatabaseObject() {};
    virtual std::string getName() const override;
    virtual library::uuid getUuid() const override;
    virtual DatabaseObjectType getType() const override;
    virtual void setName(std::string name) override;
    virtual void setLocation(std::shared_ptr<IDatabaseObject> location) override;
    virtual void getLocation(std::shared_ptr<IDatabaseObject> &location) override;

   protected:
    std::string name_;
    DatabaseObjectType type_;
    library::uuid uuid_;
    std::shared_ptr<IDatabaseObject> location_;
   private:

  };

  class DatabaseObjectDefinition {
   public:
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) {
      std::cout << "Post Setup.. none" << std::endl;
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
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) override {
      std::cout << "Post Setup.. playa" << std::endl;
      DatabaseObjectDefinition::postSetup(object);
      DatabaseObjectDefinition::setType(object, PLAYER);
    }
    static DatabaseObjectDefinitionPlayer& getInstance() {
      static DatabaseObjectDefinitionPlayer instance;
      return instance;
    }
   private:
    DatabaseObjectDefinitionPlayer() {};
    DatabaseObjectDefinitionPlayer(DatabaseObjectDefinitionPlayer const&);
    void operator=(DatabaseObjectDefinitionPlayer const&);
  };

  class DatabaseObjectDefinitionRoom : public DatabaseObjectDefinition {
   public:
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) override {
      std::cout << "Post Setup.. room" << std::endl;
      DatabaseObjectDefinition::postSetup(object);
      DatabaseObjectDefinition::setType(object, ROOM);
    }
    static DatabaseObjectDefinitionRoom& getInstance() {
      static DatabaseObjectDefinitionRoom instance;
      return instance;
    }
   private:
    DatabaseObjectDefinitionRoom() {};
    DatabaseObjectDefinitionRoom(DatabaseObjectDefinitionRoom const&);
    void operator=(DatabaseObjectDefinitionRoom const&);
  };


  class DatabaseFactory {
   public:
    bool buildObject(DatabaseObjectDefinition& definition,
                     std::shared_ptr<DatabaseObject>& newObject) {
      if (!definition.factory(newObject)) {
        // TODO(msmith): Log an error.
        return false;
      }

      newObject->uuid_ = library::generate_uuid();
      std::cout << "Post Setup.." << std::endl;
      definition.postSetup(newObject);

      return true;
    }
  };

}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECT_H_
