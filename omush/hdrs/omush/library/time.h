/**
 * \file time.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUHS_HDRS_OMUSH_LIBRARY_TIME
#define OMUHS_HDRS_OMUSH_LIBRARY_TIME

#include "boost/date_time/posix_time/posix_time_types.hpp"

namespace omush {
  namespace library {

typedef boost::posix_time::time_duration time_duration;
typedef boost::posix_time::ptime time;

inline time currentTime() {
return boost::posix_time::second_clock::universal_time();
}

  }  // namespace library

} // omush

#endif //  OMUHS_HDRS_OMUSH_LIBRARY_UUID
