/**
 * \file log.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUHS_HDRS_OMUSH_LIBRARY_LOG_H_
#define OMUHS_HDRS_OMUSH_LIBRARY_LOG_H_

#include <stdio.h>

namespace omush {
  namespace library {
    void log(std::string str) {
      printf("%s\n", str.c_str());
    }
  }  // namespace log
}  // namespace omush

#endif  // OMUHS_HDRS_OMUSH_LIBRARY_LOG_H_
