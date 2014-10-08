/**
 * \file look.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LOOK_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LOOK_H_

#include "omush/actions/action.h"
#include "omush/scope.h"
#include "omush/database/idatabaseobject.h"

namespace omush {
  namespace actions {

    /**
     * Action class for an object to 'look' at another object.
     */
    class Look : public Action {
     public:
      /**
       * Default constructor. Nothing special is setup.
       *
       * Will register strings used in this action with the Strings library the
       * first time a Connect action is used.
       */
      Look();

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
      library::OString nameLine_(std::shared_ptr<ActionScope> scope);
      library::OString descriptionLine_(std::shared_ptr<ActionScope> scope);
      library::OString exitsLine_(std::shared_ptr<ActionScope> scope);
      library::OString contentsLine_(std::shared_ptr<ActionScope> scope);


      /**
       * A shared pointer to the DatabaseObject of the target object.
       */
      std::shared_ptr<IDatabaseObject> target_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LOOK_H_
