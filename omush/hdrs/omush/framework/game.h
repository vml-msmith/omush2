/**
 * \file game.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_

#include "omush/framework/igame.h"

namespace omush {
  class Game : public IGame {
   public:
    Game();
    virtual ~Game();
    virtual bool isInitialized() const override;
    virtual bool initialize(IGameInstance* instance) override;
    virtual bool initialize(IGameInstance* instance, IGameBuilder* builder);
    virtual bool loop() const override;

   private:
    bool initialized_;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_GAME_H_
