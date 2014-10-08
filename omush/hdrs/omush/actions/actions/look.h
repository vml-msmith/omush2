/**
 * \file look.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LOOK_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LOOK_H_

#include "omush/actions/iaction.h"
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {

    /**
     * Action class for an object to 'look' at another object.
     */
    class Look : public IAction {
     public:
      /**
       * Default constructor. Nothing special is setup.
       */
      Look();

      /**
       * Set the player object that is doing the "looking".
       *
       * @param Object - Shared pointer to the DatabaseObject that is looking.
       */
      void setPlayer(std::shared_ptr<IDatabaseObject> object);

      /**
       * Set the target of the look. This is the item tthe looker looks at.
       *
       * @param Object - Shared pointer to the DatabaseObject that is being
       *        looked at.
       */
      void setTarget(std::shared_ptr<IDatabaseObject> object);

      /**
       * Run the Look action.
       *
       * If setPlayer() or setTarget() were not successfully called with a valid
       * DatabaseObject before this call, this call will do nothing.
       *
       * @param scope - ActionScope for the action.
       */
      void enact(std::shared_ptr<ActionScope> scope) override;

     private:
      std::shared_ptr<IDatabaseObject> player_;
      std::shared_ptr<IDatabaseObject> target_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LOOK_H_
