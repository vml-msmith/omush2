/**
 * \file setattribute.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/setattribute.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/library/log.h"
#include "omush/framework/strings.h"
#include "omush/database/utilities.h"

namespace omush {
  namespace actions {
    SetAttribute::SetAttribute() : attribute_(""), value_("") {
      setEnactor(nullptr);
      setTarget(nullptr);
    }

    void SetAttribute::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    void SetAttribute::setValue(std::string value) {
      value_ = value;
    }

    void SetAttribute::setAttribute(std::string attribute) {
      attribute_ = attribute;
    }

    void SetAttribute::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::SetAttribute called without an enactor.");
        return;
      }
      if (attribute_ == "") {
        library::log("action::SetAttribute called without an attribute.");
        return;
      }
      if (target_ == NULL || target_ == nullptr) {
        library::log("action::SetAttribute called without a target.");
        return;
      }


      // TODO(msmith): Check permissions.
      // TODO(msmith): Extract out attribute tree.
      target_->setAttribute(attribute_, value_);
      Notifier::notify(NULL,
                       enactor_,
                       library::OString("Set."),
                       scope);
    }

  }  // namespace actions
}  // namespace omush
