/**
 * \file databaseobjectdefitionroom.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONROOM_H_
#define OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONROOM_H_

#include "omush/database/databaseobjectdefinition.h"

namespace omush {
  class DatabaseObjectDefinitionRoom : public DatabaseObjectDefinition {
   public:
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) override {
      DatabaseObjectDefinition::postSetup(object);
      DatabaseObjectDefinition::setType(object, PLAYER);
    }
    static DatabaseObjectDefinitionRoom& getInstance() {
      static DatabaseObjectDefinitionRoom instance;
      return instance;
    }
   private:
    DatabaseObjectDefinitionRoom() {}
    DatabaseObjectDefinitionRoom(DatabaseObjectDefinitionRoom const&);
    void operator=(DatabaseObjectDefinitionRoom const&);
  };

}  // namespace omush
#endif  // OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONROOM_H_
