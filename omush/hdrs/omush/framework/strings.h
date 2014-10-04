/**
 * \file strings.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_STRINGS_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_STRINGS_H_

#include <string>
#include <map>

namespace omush {
  class Strings {
   public:
    static std::string get(std::string key);
    static Strings& getInstance() {
      static Strings    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
      return instance;
    }
    std::string _get(std::string key);
   private:
    std::map<std::string, std::string> _map;

    Strings();
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    Strings(Strings const&);              // Don't Implement
    void operator=(Strings const&); // Don't implement
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_STRINGS_H_
