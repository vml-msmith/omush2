/**
 * \file measure.h
 *
 * Copyright 2016 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_DEVELOPMENT_MEASURE_H_
#define OMUSH_HDRS_OMUSH_DEVELOPMENT_MEASURE_H_

#include <chrono>

namespace omush {
  namespace devel {

    template<typename TimeT = std::chrono::nanoseconds>
      struct measure {
        template<typename F, typename ...Args>
          static typename TimeT::rep execution(F&& func, Args&&... args) {
          auto start = std::chrono::system_clock::now();
          std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
          auto duration = std::chrono::duration_cast< TimeT>
          (std::chrono::system_clock::now() - start);
          return duration.count();
        }
      };
  }  // namespace devel
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_DEVELOPMENT_MEASURE_H_
