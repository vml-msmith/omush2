/**
 * \file commandqueue.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_QUEUE_COMMANDQUEUE_H_
#define OMUSH_HDRS_OMUSH_QUEUE_COMMANDQUEUE_H_

#include "omush/queue/icommandqueue.h"
#include "omush/commands/icommandparser.h"

namespace omush {
  class CommandQueue : public ICommandQueue {
   public:
    CommandQueue();
    ~CommandQueue();
    virtual bool loop(IGameInstance *gameInstance, QueueObjectQueue *discard);
    virtual bool addQueueObject(QueueObject object);
   private:
    std::shared_ptr<ICommandParser> commandParser_;
    QueueObjectQueue queue_;
  };
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_QUEUE_COMMANDQUEUE_H_
