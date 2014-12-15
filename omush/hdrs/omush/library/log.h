/**
 * \file log.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUHS_HDRS_OMUSH_LIBRARY_LOG_H_
#define OMUHS_HDRS_OMUSH_LIBRARY_LOG_H_

#include <string>

namespace omush {
  namespace library {
    enum LogLevel { 
      INFO = 0x01,
      WARNING = 0x02, 
      ERROR = 0x04,
      NOTICE = 0x08,
      CRASH = 0x002,
    };
    
    void log(std::string str, LogLevel level);

    void log(std::string str);
  }  // namespace log
}  // namespace omush

#endif  // OMUHS_HDRS_OMUSH_LIBRARY_LOG_H_
