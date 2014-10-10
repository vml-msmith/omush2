/**
 * \file stringfunctions.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/library/string.h"

namespace omush {
  namespace library {
    namespace string {
      std::string &ltrim(std::string &s,
                         const std::string &chars) {
        s.erase(s.begin(),
                std::find_if(s.begin(),
                             s.end(),
                             [&](char c) {
                               return chars.find(c) == std::string::npos;
                             }));
        return s;
      }

      std::string &rtrim(std::string &s,
                         const std::string &chars) {
        s.erase(std::find_if(s.rbegin(),
                             s.rend(),
                             [&](char c) {
                               return chars.find(c) == std::string::npos;
                             }).base(),
                s.end());
        return s;
      }

      std::string &trim(std::string &s,
                        const std::string &chars) {
        return ltrim(rtrim(s, chars), chars);
      }

      void to_upper(std::string &str) {
        return boost::to_upper(str);
      }

      void to_lower(std::string &str) {
        return boost::to_lower(str);
      }

      bool iequals(std::string left, std::string right) {
        return boost::iequals(left, right);
      }

      void replace_all(std::string &in, std::string search, std::string replace) {
        return boost::replace_all(in, search, replace);
      }
    }
  }
}
