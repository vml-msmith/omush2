/**
 * \file databaseobjectdefitionthing.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONTHING_H_
#define OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONTHING_H_

#include "omush/database/databaseobjectdefinition.h"

namespace omush {
  class DatabaseObjectDefinitionThing : public DatabaseObjectDefinition {
   public:
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) override {
      DatabaseObjectDefinition::postSetup(object);
      DatabaseObjectDefinition::setType(object, THING);
    }
    static DatabaseObjectDefinitionThing& getInstance() {
      static DatabaseObjectDefinitionThing instance;
      return instance;
    }
   private:
    DatabaseObjectDefinitionThing() {}
    DatabaseObjectDefinitionThing(DatabaseObjectDefinitionThing const&);
    void operator=(DatabaseObjectDefinitionThing const&);
  };

}  // namespace omush
#endif  // OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONTHING_H_
