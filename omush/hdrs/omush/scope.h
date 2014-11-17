/**
 * \file scope.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_SCOPE_H_
#define OMUSH_HDRS_OMUSH_SCOPE_H_

#include <string>
#include "omush/network/common.h"
#include "omush/library/uuid.h"
#include "omush/database/idatabaseobject.h"
#include "omush/framework/gameinstance.h"


namespace omush {
  /**
   * Forward declaration of IGameInstance.
   */
  class IGameInstance;

  /*
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
  */

  /**
   * Scope object for commands in the command "queue"s.
   */
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

  /**
   * Scope object once a command has moved from a "Queue" to a "Command".
   *
   * This scope includes the QueueObject it was created from.
   */
  struct CommandScope {
    std::shared_ptr<QueueObject> queueObject;
    // Command specific things that do no perkalate.
  };

  /**
   * Scope object once a command has moved to an Action.
   *
   * This scope includes the QueueObject and the CommandScope that it was
   * created from.
   */
  struct ActionScope {
    std::shared_ptr<CommandScope> commandScope;
    std::shared_ptr<QueueObject> queueObject;
    // Action specific things that do no perkalate.
  };

  struct ActionResponse {
  };


  /**
   * Scope object once an Action (or possibly command) needs to use execute
   * code.
   *
   * This scope includes the QueueObject, CommandScope and ActionScope it was
   * created from.
   */
  struct FunctionScope {
    std::shared_ptr<ActionScope> actionScope;
    std::shared_ptr<CommandScope> commandScope;
    std::shared_ptr<QueueObject> queueObject;

    int depth;
    bool trace;
    FunctionScope() : depth(0) {}
  };

  struct FunctionResponse {
  };

  /**
   * Create an ActionScope shared_ptr from a CommandScope.
   *
   * @paramm scope - The CommandScope the ActionScope is created from.
   *
   * @return shared_ptr to a new ActionScope.
   */
  inline std::shared_ptr<ActionScope>
    makeActionScope(std::shared_ptr<CommandScope> scope) {
    std::shared_ptr<ActionScope> aScope(new ActionScope());
    aScope->commandScope = scope;
    aScope->queueObject = scope->queueObject;
    return aScope;
  }

  /**
   * Create a FunctionScope shared_ptr from an ActionScope.
   *
   * @paramm scope - The ActionScope this FunctionScope is created from.
   *
   * @return shared_ptr to a new FunctionScope.
   */
  inline std::shared_ptr<FunctionScope>
    makeFunctionScope(std::shared_ptr<ActionScope> scope) {
    std::shared_ptr<FunctionScope> fScope(new FunctionScope());
    fScope->actionScope = scope;
    fScope->commandScope = scope->commandScope;
    fScope->queueObject = scope->queueObject;

    return fScope;
  }
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_SCOPE_H_
