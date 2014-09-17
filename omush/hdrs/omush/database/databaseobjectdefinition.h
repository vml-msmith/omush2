/**
 * \file databaseobjectdefinition.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECTDEFINITION_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASEOBJECTDEFINITION_H_

#include "omush/database/databaseobject.h"

namespace omush {
  class DatabaseObject;

  class DatabaseObjectDefinition {
   public:
    virtual void postSetup(std::shared_ptr<DatabaseObject> &object) {
    }

    virtual bool factory(std::shared_ptr<DatabaseObject> &object) {
      object = std::shared_ptr<DatabaseObject>(new DatabaseObject());
      return true;
    }

   protected:
    void setType(std::shared_ptr<DatabaseObject> &object,
                 DatabaseObjectType type) {
      object->type_ = type;
    }
    DatabaseObjectDefinition() {
    }
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DARABASE_DATABASEOBJECTDEFINITION_H_
