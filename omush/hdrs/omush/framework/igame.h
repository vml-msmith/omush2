/**
 * \file igame.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_IGAME_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_IGAME_H_

namespace omush {
  struct IGameInstance;
  class IGame {
   public:
    IGame() {}
    virtual ~IGame() {}
    virtual bool isInitialized() const = 0;
    virtual bool initialize(IGameInstance* instance) = 0;
   private:
  };
} // omush

#endif //  OMUSH_HDRS_OMUSH_FRAMEWORK_IGAME_H_
