/**
 * \file igameinstance.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMEINSTANCE_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMEINSTANCE_H_

namespace omush {
  class IGame;
  struct IGameInstance {
    IGame* game;
    IGameInstance() : game(nullptr) {};
  };
} // omush

#endif //  OMUSH_HDRS_OMUSH_FRAMEWORK_IGAMEINSTANCE_H_
