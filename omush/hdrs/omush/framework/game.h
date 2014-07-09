/**
 * \file game.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_

#include "igame.h"

namespace omush {
  class Game : public IGame {
   public:
    Game();
    virtual ~Game();
    virtual bool isInitialized() const override;
    virtual bool initialize(IGameInstance* instance) override;

   private:
    bool initialized_;
  };
} // omush

#endif //  OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_
