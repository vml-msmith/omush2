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
#include "omush/database/idatabaseobject.h"
#include "omush/framework/gameinstance.h"


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

    bool getExecutorObject(std::shared_ptr<IDatabaseObject>& object) {
      return gameInstance->database->getObjectByUUID(executor, object);
    }

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
    std::shared_ptr<CommandScope> commandScope;
    std::shared_ptr<QueueObject> queueObject;
  };

  struct FunctionResponse {
  };


  inline std::shared_ptr<ActionScope>
    makeActionScope(std::shared_ptr<CommandScope> scope) {
    std::shared_ptr<ActionScope> aScope(new ActionScope());
    aScope->commandScope = scope;
    aScope->queueObject = scope->queueObject;
    return aScope;
  }

  inline std::shared_ptr<FunctionScope>
    makeFunctionScope(std::shared_ptr<ActionScope> scope) {
    std::shared_ptr<FunctionScope> fScope(new FunctionScope());
    fScope->actionScope = scope;
    fScope->commandScope = scope->commandScope;
    fScope->queueObject = scope->queueObject;

    return fScope;
  }
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_SCOPE_H_
