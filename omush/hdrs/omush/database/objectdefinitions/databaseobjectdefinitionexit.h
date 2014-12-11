/**
 * \file databaseobjectdefitionexit.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONEXIT_H_
#define OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONEXIT_H_

#include "omush/database/databaseobjectdefinition.h"

namespace omush {
  class DatabaseObjectDefinitionExit : public DatabaseObjectDefinition {
   public:
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) override {
      DatabaseObjectDefinition::postSetup(object);
      DatabaseObjectDefinition::setType(object, EXIT);
    }
    static DatabaseObjectDefinitionExit& getInstance() {
      static DatabaseObjectDefinitionExit instance;
      return instance;
    }
   private:
    DatabaseObjectDefinitionExit() {}
    DatabaseObjectDefinitionExit(DatabaseObjectDefinitionExit const&);
    void operator=(DatabaseObjectDefinitionExit const&);
  };

}  // namespace omush
#endif  // OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONEXIT_H_
