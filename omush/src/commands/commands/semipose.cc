/**
 * \file semipose.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/semipose.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/database/databaseobject.h"

#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/actions/actions/semipose.h"

namespace omush {
  namespace command {

    std::string SemiPoseDefinition::name() {
      return "SEMI-POSE";
    }

    std::unique_ptr<ICommand> SemiPoseDefinition::factory() {
      return std::unique_ptr<ICommand>(new SemiPose);
    }

    std::vector<std::string> SemiPoseDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("semi-pose (.+)");
      patterns.push_back("; (.+)");
      patterns.push_back(";(.+)");

      return patterns;
    }

    SemiPose::SemiPose() {
    }

    bool SemiPose::execute(std::shared_ptr<CommandScope> scope) {
      SemiPoseDefinition def;
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);

      std::string say;
      std::vector<std::string> patterns = def.patterns();
      for (auto p : patterns) {
        try {
          std::regex rx(p.c_str(), std::regex::icase);
          std::smatch what;
          if (std::regex_match(queueObject->originalString, what, rx)) {
            for (size_t i = 0; i < what.size(); ++i) {
              std::ssub_match sub_match = what[i];
              std::string piece = sub_match.str();
            }
            say = what[1];
            break;
          }
        } catch (std::regex_error &e) {
          library::log(std::string(e.what()) +
                       " " +
                       library::parseRegexErrorCode(e.code()));
        }
      }



      std::shared_ptr<IDatabaseObject> object;
      if (scope->queueObject->gameInstance->database->getObjectByUUID(scope->queueObject->executor,
                                                                      object)) {

        actions::SemiPose poseAction;
        poseAction.setPlayer(object);
        poseAction.setText(say);
        poseAction.enact(makeActionScope(scope));
      }
      else {
        // TODO: Log this.
      }

      return true;
    }

  }  // namespace command
}  // namespace omush
