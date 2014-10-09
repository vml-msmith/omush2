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
       *
       * This action will do a number of things....
       *   - Notify the enactor of all the look components.
       *   - Notify the target he was looked at by enactor.
       *   - Notify the looker's surroundings that he looked.
       *   - Execute the @alook attribute of the target.
       *
       * @param scope - ActionScope for the action.
       */
      void enact(std::shared_ptr<ActionScope> scope) override;

     private:
      /**
       * Get the name of the target object and format it based on the looker.
       *
       * // TODO: Add @nameformat.
       *
       * @param scope - ActionScope for the action.
       *
       * @return String ready to be displayed to the looker object.
       */
      library::OString nameLine_(std::shared_ptr<ActionScope> scope);

      /**
       * Evaluate the description attribute of the target and format for the
       * looker.
       *
       * // TODO: Add @descformat.
       *
       * @param scope - ActionScope for the action.
       *
       * @return String ready to be displayed to the looker object.
       */
      library::OString descriptionLine_(std::shared_ptr<ActionScope> scope);

      /**
       * Display Exits with a list of exits IF there are exits from the target.
       *
       * If there are no exits opened from the target, nothing will be
       * displayed.
       *
       * // TDOO: Add @exitformat and @columnate
       *
       * @param scope - ActionScope for the action.
       *
       * @return String ready to be displayed to the looker object.
       */
      library::OString exitsLine_(std::shared_ptr<ActionScope> scope);

      /**
       * Display contents that are in the target.
       *
       * If there are no contents in the target, this will return nothing..
       *
       * // TDOO: Add @conformat.
       *
       * @param scope - ActionScope for the action.
       *
       * @return String ready to be displayed to the looker object.
       */
      library::OString contentsLine_(std::shared_ptr<ActionScope> scope);

      /**
       * A shared pointer to the DatabaseObject of the target object.
       */
      std::shared_ptr<IDatabaseObject> target_;
    };
  }  // namespace actions
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONS_LOOK_H_
