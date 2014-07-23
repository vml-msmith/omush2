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

namespace omush {
class IGameInstance;
  struct QueueObject {
    // Descriptor ID.
    IGameInstance* gameInstance;
    DescriptorID descId;
    std::string originalString;
    std::string calledString;

    // Message
    // Dbref of object.
    // Init time?
    // Caller
    // Enactor
    // Executor
  };

  typedef std::queue<QueueObject> QueueObjectQueue;

  class ICommandQueue {
   public:
    ICommandQueue() {}
    ~ICommandQueue() {};
    virtual bool loop(IGameInstance* gameInstance, QueueObjectQueue *discard) = 0;
    virtual bool addQueueObject(QueueObject object) = 0;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_QUEUE_ICOMMANDQUEUE_H_
