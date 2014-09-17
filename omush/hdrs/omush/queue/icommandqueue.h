/**
 * \file icommandqueue.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_QUEUE_ICOMMANDQUEUE_H_
#define OMUSH_HDRS_OMUSH_QUEUE_ICOMMANDQUEUE_H_

#include <queue>
#include "omush/network/common.h"
#include "omush/framework/igameinstance.h"
//#include "omush/library/uuid.h"
#include "omush/scope.h"

namespace omush {
  class IGameInstance;

  typedef std::queue<std::shared_ptr<QueueObject>> QueueObjectQueue;

  class ICommandQueue {
   public:
    ICommandQueue() {}
    ~ICommandQueue() {};
    virtual bool loop(IGameInstance* gameInstance, QueueObjectQueue *discard) = 0;
    virtual bool addQueueObject(std::shared_ptr<QueueObject> object) = 0;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_QUEUE_ICOMMANDQUEUE_H_
