/**
 * \file databaseobjectdefitionplayer.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONPLAYER_H_
#define OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONPLAYER_H_

#include "omush/database/databaseobjectdefinition.h"

namespace omush {
  class DatabaseObjectDefinitionPlayer : public DatabaseObjectDefinition {
   public:
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) override {
      DatabaseObjectDefinition::postSetup(object);
      DatabaseObjectDefinition::setType(object, PLAYER);
    }
    static DatabaseObjectDefinitionPlayer& getInstance() {
      static DatabaseObjectDefinitionPlayer instance;
      return instance;
    }
   private:
    DatabaseObjectDefinitionPlayer() {}
    DatabaseObjectDefinitionPlayer(DatabaseObjectDefinitionPlayer const&);
    void operator=(DatabaseObjectDefinitionPlayer const&);
  };

}  // namespace omush
#endif  // OMUSH_HDRS_OMUSH_DATABASE_OBJECTDEFINITIONS_DATABASEOBJECTDEFINITIONPLAYER_H_
