/**
 * \file regex.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/library/regex.h"
#include <map>
#include <queue>
#include <string>

namespace omush {
  namespace library {
    bool regex_named_match(std::string str,
                           std::string matchString,
                           std::map<std::string,std::string>& matches) {
      std::size_t pos;
      std::size_t start = 0;
      std::queue<std::string> groupNames;
      groupNames.push("whole_string");
      pos = matchString.find("?P<");
      while (pos != std::string::npos) {
        start = pos;
        std::size_t end = matchString.find(">", pos + 1);
        std::string name = matchString.substr(pos + 3, end - 3 - pos);
        groupNames.push(name);
        matchString.erase(pos,end - pos + 1);
        pos = matchString.find("?P<");
      }


      std::regex rx(matchString, std::regex::icase);
      std::smatch what;
      if (std::regex_match(str, what, rx)) {
        for (size_t i = 0; i < what.size(); ++i) {
          std::ssub_match sub_match = what[i];
          std::string piece = sub_match.str();
          std::string name = piece;

          if (!groupNames.empty()) {
            name = groupNames.front();
            groupNames.pop();
          }

          matches.insert(std::pair<std::string,std::string>(name,
                                                            piece));
        }
        return true;
      }
      else {
        return false;
      }
    }

  }  // namespace library
}  // namespace omush
