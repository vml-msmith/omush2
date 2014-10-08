/**
 * \file connect.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_CONNECT_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_CONNECT_H_

#include "omush/actions/action.h"
#include "omush/scope.h"
#include "omush/database/databaseobject.h"
#include "omush/library/string.h"

namespace omush {
  namespace actions {

    /**
     * Action class to connect a player to the game and run any actions
     * associated with logging in.
     */
    class Connect : public Action {
     public:
      /**
       * Default constructor.
       *
       * Will register strings used in this action with the Strings library the
       * first time a Connect action is used.
       */
      Connect();

      /**
       * Set the player object to be connected.
       *
       * Must be called before enact.
       *
       * @param object - Shared pointer to the DatabaseObject that will be
       *                 connected.
       */
      void setPlayer(std::shared_ptr<IDatabaseObject> object);

      /**
       * Run the Connect action for the player set in setPlayer().
       *
       * setPlayer() must be called before this method, or the method will fail.
       *
       * This action will do a number of things....
       *   - Notify the surroundings of the player that he has logged in.
       *   - Notify the player he has logged in.
       *   - Trigger aconnect on object (TODO)
       *   - Trigger aconnect on room (TODO)
       *   - Trigger aconnect on global objects (TODO)
       *   - Trigger aconnect on channels (TODO).
       *   - Call actions::Look for the player with his location as the target.
       *
       * @param scope - ActionScope for the action.
       */
      void enact(std::shared_ptr<ActionScope> scope) override;

      /**
       * Callback to create a string To display to the object when the target
       * of the action connects.
       *
       * This message can change based on who it's being sent to.
       *   - The player_ will see "You have connected..."
       *   - Others will see "Name has connected." Name may changed based on
       *     the object param.
       *
       * @param object - The object that will be notified player_ has logged
       *        in.
       */
      library::OString playerHasConnectedString(
          std::shared_ptr<IDatabaseObject> object);

     private:
      /**
       * Trigger code in the @aconnect attribute of the connecting object.
       *
       * TODO(msmith): Implement this method.
       * TODO(msmith): List the replacements for the function call.
       *
       * @param scope - ActionScope for the action.
       */
      void doTriggerAConnectObject_(std::shared_ptr<ActionScope> scope);

      /**
       * Trigger code in the @aconnect attribute of location of the connecting
       * object.
       *
       * TODO(msmith): Implement this method.
       * TODO(msmith): List the replacements for the function call.
       *
       * @param scope - ActionScope for the action.
       */
      void doTriggerAConnectLocation_(std::shared_ptr<ActionScope> scope);

      /**
       * Trigger @aconnect attribute of any objects in teh global room or
       * global zone.
       *
       * TODO(msmith): Implement this method.
       * TODO(msmith): List the replacements for the function call.
       *
       * @param scope - ActionScope for the action.
       */
      void doTriggerAConnectGlobal_(std::shared_ptr<ActionScope> scope);

      /**
       * Notify any objects that need to know the object has connected.
       *
       * This will notify:
       *  - The connecting object that they have connected.
       *  - The location and all objects in the location of the object.
       *
       * NOTE: Notifications are subject to what the objects being notifed can
       *       actually "see". Hidden or dark objects may not be seeable.
       *
       * @param scope - ActionScope for the action.
       */
      void doConnectNotify_(std::shared_ptr<ActionScope> scope);

      /**
       * Start an actions::Look action with the connecting object as the looker
       * and the object's location as the target.
       *
       * @param scope - ActionScope for the action.
       */
      void doLook_(std::shared_ptr<ActionScope> scope);

      /**
       * A shared pointer to the DatabaseObject of the connecting player.
       */
      std::shared_ptr<IDatabaseObject> player_;

      /**
       * ActionScope passed into enact. Saved her so it may be used in
       * playerHasConnectedString.
       */
      std::shared_ptr<ActionScope> scope_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_CONNECT_H_
