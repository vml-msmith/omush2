/**
 * \file notifier.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_NOTIFIER_H_
#define OMUSH_HDRS_OMUSH_NOTIFIER_H_

#include <memory>
#include "omush/database/idatabase.h"
#include "omush/database/playerobject.h"
#include "omush/scope.h"
#include "omush/network/common.h"
#include "omush/library/string.h"
#include <boost/bind.hpp>

namespace omush {
  typedef boost::function<library::OString(std::shared_ptr<IDatabaseObject> listener)> NotifyCallback;

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

    static void notifySurroundings(IDatabase *db,
                                   std::shared_ptr<IDatabaseObject> object,
                                   NotifyCallback callback,
                                   std::shared_ptr<ActionScope> scope) {
      // Create a map of listeners.
      std::map<library::uuid, std::shared_ptr<IDatabaseObject>> listeners;

      // Add objects to the listeners. This gets added with locatins contents.
      //      listeners[object->getUuid()] = object;

      // Get the room, add it to the listeners.
      std::shared_ptr<IDatabaseObject> location = nullptr;
      object->getLocation(location);
      if (location != nullptr) {
        listeners[location->getUuid()] = location;

        // Get location contents.
        std::vector<std::shared_ptr<IDatabaseObject>> contents;
        location->getContents(contents);
        for (auto item : contents) {
          listeners[item->getUuid()] = item;
        }

        // TODO(msmith): Notifiy exits that are "open".
      }

      // Get object contents.
      for (auto& it : listeners) {
        library::OString str;
        str = callback(it.second);
        printf("Final\n");
        Notifier::notify(NULL, it.second, str, scope);
      }
    }

   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_NOTIFIER_H_
