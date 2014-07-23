/**
 * \file string.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_LIBRARY_STRING_H_
#define OMUSH_HDRS_OMUSH_LIBRARY_STRING_H_

#include <boost/algorithm/string.hpp>
#include <string>

namespace omush {
  namespace library {
    namespace string {
      inline bool iequals(std::string left, std::string right) {
        return boost::iequals(left, right);
      }
    }  // namespace string
  }  // namespace library
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_LIBRARY_STRING_H_
