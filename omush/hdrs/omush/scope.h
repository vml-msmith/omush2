/**
 * \file scope.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_SCOPE_H_
#define OMUSH_HDRS_OMUSH_SCOPE_H_

//#include "omush/framework/igameinstance.h"
#include "omush/network/common.h"
#include "omush/library/uuid.h"

namespace omush {
  class IGameInstance;
  struct Scope {
  public:
    IGameInstance* gameInstance;
    DescriptorID descId;
    std::string originalString;
    std::string calledString;

    library::uuid enactor;
    library::uuid executor;
    library::uuid caller;
    Scope() {
      enactor = library::generate_null_uuid();
      executor = library::generate_null_uuid();
      caller = library::generate_null_uuid();
    }
  };


  struct QueueObject {
    IGameInstance* gameInstance;
    DescriptorID descId;
    std::string originalString;
    std::string calledString;

    library::uuid enactor;
    library::uuid executor;
    library::uuid caller;
    QueueObject() {
      enactor = library::generate_null_uuid();
      executor = library::generate_null_uuid();
      caller = library::generate_null_uuid();
    }
  };

  struct CommandScope {
    std::shared_ptr<QueueObject> queueObject;
    // Command specific things that do no perkalate.
  };

  struct ActionScope {
    std::shared_ptr<CommandScope> commandScope;
    std::shared_ptr<QueueObject> queueObject;
    // Action specific things that do no perkalate.
  };

  struct ActionResponse {
  };


  struct FunctionScope {
    std::shared_ptr<ActionScope> actionScope;
  };

  struct FunctionResponse {
  };


  inline std::shared_ptr<ActionScope> makeActionScope(std::shared_ptr<CommandScope> scope) {
    std::shared_ptr<ActionScope> aScope(new ActionScope());
    aScope->commandScope = scope;
    aScope->queueObject = scope->queueObject;
    return aScope;
  }
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_SCOPE_H_
