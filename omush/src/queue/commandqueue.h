/**
 * \file descriptorcommandqueue.h
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/queue/descriptorcommandqueue.h"
#include "omush/commands/commandparser.h"
#include "omush/commands/commands/quit.h"

namespace omush {
  DescriptorCommandQueue::DescriptorCommandQueue() {
    commandParser_ = std::shared_ptr<ICommandParser>(new CommandParser());
    commandParser_->registerCommand(CommandDefinitionPtr(new command::QuitDefinition()));

  }

  DescriptorCommandQueue::~DescriptorCommandQueue() {
  }

  bool DescriptorCommandQueue::loop(QueueObjectQueue *discard) {
    while (!queue_.empty()) {
      QueueObject object = queue_.front();
      queue_.pop();
      ICommandDefinition *def;
      if (commandParser_->matchCommand(object.originalString, def)) {
        printf("Yay!\n");
      } else {
        if (discard != NULL) {
          discard->push(object);
        }
      }
    }

    return false;
  }

  bool DescriptorCommandQueue::addQueueObject(QueueObject object) {
    queue_.push(object);
    return true;
  }

}  // namespace omush
