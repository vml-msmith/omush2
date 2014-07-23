/**
 * \file descriptorcommandqueue.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_QUEUE_DESCRIPTORCOMMANDQUEUE_H_
#define OMUSH_HDRS_OMUSH_QUEUE_DESCRIPTORCOMMANDQUEUE_H_

#include "omush/queue/commandqueue.h"
#include "omush/commands/icommandparser.h"

namespace omush {
  class DescriptorCommandQueue : public CommandQueue {
   public:
    DescriptorCommandQueue();
    ~DescriptorCommandQueue();
    virtual bool loop(IGameInstance* gameInstance, QueueObjectQueue *discard);
    virtual bool addQueueObject(QueueObject object);
   private:
    std::shared_ptr<ICommandParser> commandParser_;
    QueueObjectQueue queue_;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_QUEUE_DESCRIPTORCOMMANDQUEUE_H_
