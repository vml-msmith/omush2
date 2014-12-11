/**
 * \file look.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/actions/actions/look.h"
#include "omush/framework/igame.h"
#include "omush/framework/igameinstance.h"
#include "omush/framework/strings.h"
#include "omush/functions/iexpressionengine.h"
#include "omush/library/string.h"
#include "omush/notifier.h"
#include "omush/library/log.h"
#include "omush/database/nameformatter.h"

namespace omush {
  namespace actions {
    Look::Look() : target_(nullptr) {
      static bool hasAddedStrings = false;
      setEnactor(nullptr);
      if (hasAddedStrings == false) {
        Strings::ReplaceMap items;
        /*
        items["ACTION_CONNECT__YOU_HAVE_CONNECTED"] =
          "You have connected...";
        items["ACTION_CONNECT__OTHER_HAS_CONNECTED"] =
          "!playerName has connected.";
        */
        registerStrings_(items);
      }
    }

    void Look::setTarget(std::shared_ptr<IDatabaseObject> object) {
      target_ = object;
    }

    void Look::enact(std::shared_ptr<ActionScope> scope) {
      if (enactor_ == NULL || enactor_ == nullptr) {
        library::log("action::Look called without an enactor.");
        return;
      }

      if (target_ == NULL || target_ == nullptr) {
        library::log("action::Look called without a target.");
        return;
      }

      library::string::OString lines;

      lines += nameLine_(scope);
      lines += descriptionLine_(scope);
      lines += exitsLine_(scope);
      lines += contentsLine_(scope);

      Notifier::notify(NULL, enactor_, lines, scope);
    }

    library::OString Look::nameLine_(
        std::shared_ptr<ActionScope> scope) {
      // TODO(msmith): Add @nameformat here.
      //               That can be a flag to NameFormatter::

      library::OString name;
      NameFormatter::format(scope,
                            enactor_,
                            target_,
                              NameFormatter::Flags::COLORED |
                              NameFormatter::Flags::DBREF |
                              NameFormatter::Flags::FLAGS,
                            name);
      return name;
    }

    library::OString Look::descriptionLine_(
      std::shared_ptr<ActionScope> scope) {
      // TODO(msmith): Add @descformat.

      std::string attribute;
      if (target_->getAttribute("description", attribute)) {
        library::OString parsedAttribute;
        scope->queueObject
          ->gameInstance
          ->expressionEngine
          ->parse(attribute, makeFunctionScope(scope), parsedAttribute);
        return library::OString(std::string("\n") + parsedAttribute);
      }
      return std::string("");
    }

    library::OString Look::exitsLine_(
      std::shared_ptr<ActionScope> scope) {
      // TODO(msmith): Add @exitformat.

      return std::string("");
    }

    library::OString Look::contentsLine_(
      std::shared_ptr<ActionScope> scope) {

      library::OString response;

      // TODO(msmith): Add @conformat.

      std::map<library::uuid, std::shared_ptr<IDatabaseObject>> objects;

      std::vector<std::shared_ptr<IDatabaseObject>> contents;
      target_->getContents(contents);
      for (auto item : contents) {
        objects[item->getUuid()] = item;
        library::OString name;
        NameFormatter::format(scope,
                              enactor_,
                              item,
                              NameFormatter::Flags::COLORED |
                              NameFormatter::Flags::DBREF |
                              NameFormatter::Flags::FLAGS,
                              name);
        response += library::OString("\n") + name;
      }

      return response;
    }

  }  // namespace actions
}  // namespace omush
