/**
 * \file gamebuilder.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_FRAMEWORK_GAMEBUILDER_H_
#define OMUSH_HDRS_OMUSH_FRAMEWORK_GAMEBUILDER_H_

#include "omush/framework/igamebuilder.h"

namespace omush {

  class GameBuilder : public IGameBuilder {
   public:
    GameBuilder();
    virtual bool setupNetwork(IGameInstance *instance) const override;
    virtual bool setupDatabase(IGameInstance *instance) const override;
   private:
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_FRAMEWORK_GAMEBUILDER_H_
