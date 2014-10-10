/**
 * \file who.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/commands/commands/who.h"
#include <memory>
#include <string>
#include <vector>
#include "omush/database/databaseobject.h"
#include "omush/framework/igame.h"
#include "omush/framework/game.h"
#include "omush/library/regex.h"
#include "omush/library/log.h"
#include "omush/notifier.h"
#include <boost/lexical_cast.hpp>
 #include "boost/date_time/gregorian/gregorian.hpp"

namespace omush {
  namespace command {
    using namespace boost::gregorian;

    std::string WhoDefinition::name() {
      return "WHO";
    }

    std::unique_ptr<ICommand> WhoDefinition::factory() {
      return std::unique_ptr<ICommand>(new Who);
    }

    std::vector<std::string> WhoDefinition::patterns() {
      std::vector<std::string> patterns;
      patterns.push_back("who");

      return patterns;
    }

    Who::Who() {
    }

    library::OString Who::formatOnFor(library::time_duration time) {
      int t = time.ticks() / 1000000;

      int hours = t / 3600;
      int minutes = (t - (hours * 3600)) / 60;

      std::string sHours = boost::lexical_cast<std::string>(hours);
      if (sHours.length() <= 1)
        sHours = "0" + sHours;

      std::string sMinutes = boost::lexical_cast<std::string>(minutes);
      if (sMinutes.length() <= 1)
        sMinutes= "0" + sMinutes;

      return library::OString(sHours + ":" + sMinutes);
    }

    library::OString Who::formatIdle(library::time_duration time) {
      int t = time.ticks() / 1000000;

      int hours = t/ 3600;
      if (hours > 0) {
        std::string sHours = boost::lexical_cast<std::string>(hours);
        sHours += "h";
        return sHours;
      }

      int minutes = t / 60;
      if (minutes > 0) {
        std::string sHours = boost::lexical_cast<std::string>(minutes);
        sHours += "m";
        return sHours;
      }

      int secs = t;
      return library::OString(boost::lexical_cast<std::string>(t) + "s");
    }

    library::OString Who::formatColumns(std::vector<WhoColumn> columns) {
      std::string line = "";

      for (std::vector<WhoColumn>::iterator it = columns.begin();
           it != columns.end();
           ++it) {

        // TODO(msmith): Fix this to use the correct OString manipulation
        // methods.
        std::string val = (*it).value.outString();
        size_t size = (*it).length;

        if (val.length() > size - 1) {
          val = val.substr(0, size - 1);
        }

        line += val;
        for (int i = 0; i < size - val.length(); ++i) {
          line += " ";
        }
      }

      return library::OString(line);
    }

    bool Who::execute(std::shared_ptr<CommandScope> scope) {
      WhoDefinition def;
      std::shared_ptr<QueueObject> queueObject(scope->queueObject);

      std::string params;
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
            params = what[1];
            break;
          }
        } catch (std::regex_error &e) {
          library::log(std::string(e.what()) +
                       " " +
                       library::parseRegexErrorCode(e.code()));
        }
      }

      size_t nameSize = 15;
      size_t flagSize = 8;
      size_t onForSize = 8;
      size_t idleSize = 8;
      size_t classSize = 20;
      size_t empireSize = 6;
      size_t doingSize = 15;

      std::vector<WhoColumn> columns;
      columns.push_back(WhoColumn(library::OString("Name"), nameSize));
      columns.push_back(WhoColumn(library::OString("Flags"), flagSize));
      columns.push_back(WhoColumn(library::OString("OnFor"), onForSize));
      columns.push_back(WhoColumn(library::OString("Idle"), idleSize));
      columns.push_back(WhoColumn(library::OString("Class/Pos"), classSize));
      columns.push_back(WhoColumn(library::OString("Emp"), empireSize));
      columns.push_back(WhoColumn(library::OString("Doing"), doingSize));


      library::OString output = formatColumns(columns);

      std::vector<DescriptorID> descs;
      scope->queueObject->gameInstance->game->getDescriptorList(descs);
      // TODO(msmith): Possibly sort the entries in descs.
      library::time currentTime = library::currentTime();
      for (auto iter : descs) {
        library::uuid uuid;
        if (!scope->queueObject->gameInstance->game->getObjectUUIDFromDescriptor(iter,
                                                                                uuid)) {
          continue;
        }

        std::shared_ptr<IDatabaseObject> object;
        if (!scope->queueObject->gameInstance->database->getObjectByUUID(uuid,
                                                                        object)) {
          continue;
        }

        std::shared_ptr<IGame::Connection> conn;
        if (!scope->queueObject->gameInstance->game->descriptorIDToConnection_(iter, conn)) {
          continue;
        }

        //        library::time myEpoch(boost::posix_time::date(1970,Jan,1))
        boost::posix_time::ptime time_t_epoch(date(1970,1,1));
        boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
        boost::posix_time::time_duration diff = conn->connectTime - time_t_epoch;

        // Get the logged in user.
        // Name
        columns[0].value = library::OString(object->getName());

        // Flags
        columns[1].value = formatFlagListForObject(scope->queueObject->gameInstance->database, object);

        // OnFor
        columns[2].value = formatOnFor(currentTime - conn->connectTime);

        // Idle
        columns[3].value = formatIdle(currentTime - conn->lastActiveTime);

        // Class/Pos
        columns[4].value = library::OString("...");

        // Emp
        columns[5].value = library::OString("...");

        // Doing
        columns[6].value = library::OString("...");

        output += library::OString("\n") + formatColumns(columns);
      }


      if (library::is_null(scope->queueObject->executor) &&
          !library::is_null(scope->queueObject->descId)) {
        scope->queueObject->gameInstance->game->sendNetworkMessageByDescriptor(scope->queueObject->descId,
                                                                               output.outString());
      }
      else {
        std::shared_ptr<IDatabaseObject> object;
        if (scope->queueObject->gameInstance->database->getObjectByUUID(scope->queueObject->executor,
                                                                        object)) {
          Notifier::notify(NULL, object, output.outString(), makeActionScope(scope));
        }
        else {
          // TODO: Log this.
        }
      }

      return true;
    }

    library::OString Who::formatFlagListForObject(const std::shared_ptr<IDatabase>& db,
                                                  const std::shared_ptr<IDatabaseObject>& object) {
      std::vector<std::string> f;
      f.push_back("Hidden");
      f.push_back("Haven");
      f.push_back("No_Walls");
      f.push_back("No_Gossip");

      std::string out = "";
      for (auto name : f) {
        Flag* flag = db->flags.getFlag(name);
        if (flag != NULL && object->hasFlagByBit(flag->bit)) {
          out += flag->letter;
          continue;
        }

        out += " ";
      }
      return library::OString(out);
    }
  }  // namespace command
}  // namespace omush
