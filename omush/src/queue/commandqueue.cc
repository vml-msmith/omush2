/**
 * \file commandqueue.h
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/queue/commandqueue.h"
#include "omush/commands/commandparser.h"
#include "omush/commands/commands/quit.h"

namespace omush {
  CommandQueue::CommandQueue() {
    // commandParser_ = std::shared_ptr<ICommandParser>(new CommandParser());
    //    commandParser_->registerCommand(CommandDefinitionPtr(new command::QuitDefinition()));
  }

  CommandQueue::~CommandQueue() {
  }

  bool CommandQueue::loop(IGameInstance *instance,
                          QueueObjectQueue *discard) {
    /*
    while (!queue_.empty()) {
      QueueObject object = queue_.front();
      queue_.pop();
      std::shared_ptr<ICommandDefinition> *def;
      if (commandParser_->matchCommand(object.originalString, def)) {
        printf("Yay!\n");
      } else {
        if (discard != NULL) {
          discard->push(object);
        }
      }
    }
    */
    return false;
  }

  bool CommandQueue::addQueueObject(QueueObject object) {
    queue_.push(object);
    return true;
  }

}  // namespace omush
