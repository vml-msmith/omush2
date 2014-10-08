/**
 * \file databasfactory.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DATABASE_DATABASEFACTORY_H_
#define OMUSH_HDRS_OMUSH_DATABASE_DATABASEFACTORY_H_

#include "omush/database/databaseobjectdefinition.h"

namespace omush {
  class DatabaseFactory {
   public:
    bool buildObject(DatabaseObjectDefinition& definition,
                     std::shared_ptr<DatabaseObject>& newObject) {
      if (!definition.factory(newObject)) {
        // TODO(msmith): Log an error.
        return false;
      }

      newObject->owner_ = newObject;
      newObject->uuid_ = library::generate_uuid();
      definition.postSetup(newObject);

      return true;
    }
  };

}  // namespace omush


#endif  // OMUSH_HDRS_OMUSH_DATABASE_DATABASEFACTORY_H_
