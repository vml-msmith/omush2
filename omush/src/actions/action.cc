/**
 * \file action.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/action.h"

namespace omush {
  namespace actions {
    void Action::setEnactor(std::shared_ptr<IDatabaseObject> object) {
      enactor_ = object;
    }
  }  // namespace actions
}  // namespace omush
