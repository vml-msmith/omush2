/**
 * \file descriptorcommandqueue.h
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/queue/descriptorcommandqueue.h"
#include "omush/framework/igameinstance.h"
#include "omush/commands/commandparser.h"
#include "omush/commands/commands/quit.h"
#include "omush/commands/commands/connect.h"
#include "omush/commands/absolutecommandmatcher.h"
#include "omush/commands/patterncommandmatcher.h"

namespace omush {
  DescriptorCommandQueue::DescriptorCommandQueue() {
    commandParser_ = std::shared_ptr<ICommandParser>(new CommandParser());
    commandParser_->registerCommand(CommandDefinitionPtr(new command::QuitDefinition));
    commandParser_->registerCommand(CommandDefinitionPtr(new command::ConnectDefinition));

    commandParser_->registerMatcher(std::move(std::unique_ptr<ICommandMatcher>(new AbsoluteCommandMatcher)));
    commandParser_->registerMatcher(std::move(std::unique_ptr<ICommandMatcher>(new PatternCommandMatcher)));
  }

  DescriptorCommandQueue::~DescriptorCommandQueue() {
  }

  bool DescriptorCommandQueue::loop(IGameInstance* gameInstance,
                                    QueueObjectQueue *discard) {
    while (!queue_.empty()) {
      QueueObject object = queue_.front();
      queue_.pop();

      std::shared_ptr<ICommandDefinition> def;

      if (commandParser_->matchCommand(object.originalString, def)) {
        if (def == NULL) {
          if (discard != NULL) {
            discard->push(object);
          }
        } else {
          std::unique_ptr<ICommand> cmd = def->factory();
          CommandScope scope;
          scope.originalString = object.originalString;
          scope.descId = object.descId;
          scope.gameInstance = gameInstance;

          cmd->execute(scope);
        }
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
