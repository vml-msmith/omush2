/**
 * \file notifier.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NOTIFIER_H_
#define OMUSH_HDRS_OMUSH_NOTIFIER_H_

#include "omush/database/idatabase.h"
#include "omush/database/playerobject.h"
#include "omush/scope.h"
#include "omush/network/common.h"
#include "omush/library/string.h"


namespace omush {
  class Notifier {
   public:
    Notifier();

    static void notify(IDatabase *db,
                       std::shared_ptr<IDatabaseObject> who,
                       library::OString message,
                       std::shared_ptr<ActionScope> scope) {
      DescriptorID id;
      if (scope->queueObject->gameInstance->game->getDescriptorFromObjectUUID(who->getUuid(), id)) {
        scope->queueObject->gameInstance->game->sendNetworkMessageByDescriptor(id,
                                                                               message.outString());
     }

    }
    /*
    static bool findPlayer(IDatabase *db,
                           std::string lookupString,
                           std::shared_ptr<IDatabaseObject> &object);
    */
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_NOTIFIER_H_
