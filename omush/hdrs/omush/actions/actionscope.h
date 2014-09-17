/**
 * \file actionscope.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_ACTIONS_ACTIONSCOPE_H_
#define OMUSH_HDRS_OMUSH_ACTIONS_ACTIONSCOPE_H_


namespace omush {
  namespace actions {

    struct Scope {
    public:
      IGameInstance* gameInstance;
      DescriptorID descId;
      std::string originalString;
      std::string calledString;

      library::uuid enactor;
      library::uuid executor;
      library::uuid caller;
    };
  }  // namesapce actions
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_ACTIONS_ACTIONSCOPE_H_
