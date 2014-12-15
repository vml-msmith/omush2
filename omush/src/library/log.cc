/**
 * \file log.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/library/log.h"
#include <stdio.h>
#include <string>

namespace omush {
  namespace library {
    void log(std::string str, LogLevel level) {
      printf("%s\n", str.c_str());
    }
    
    void log(std::string str) {
      log(str, LogLevel::INFO);
    }    
  }  // library
}  // namespace omush