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
#include "omush/commands/commands/help.h"
#include "omush/commands/commands/huh.h"
#include "omush/commands/commands/who.h"
#include "omush/commands/commands/welcome_screen.h"
#include "omush/commands/absolutecommandmatcher.h"
#include "omush/commands/patterncommandmatcher.h"
#include "omush/commands/commands/reconnect.h"

namespace omush {
  DescriptorCommandQueue::DescriptorCommandQueue() {
    commandParser_ = std::shared_ptr<ICommandParser>(new CommandParser());
    commandParser_->registerCommand(CommandDefinitionPtr(new command::QuitDefinition));
    commandParser_->registerCommand(CommandDefinitionPtr(new command::ConnectDefinition));
    commandParser_->registerCommand(CommandDefinitionPtr(new command::HelpDefinition));
    commandParser_->registerCommand(CommandDefinitionPtr(new command::WelcomeScreenDefinition));
    commandParser_->registerCommand(CommandDefinitionPtr(new command::HuhDefinition));
    commandParser_->registerCommand(CommandDefinitionPtr(new command::WhoDefinition));
    commandParser_->registerCommand(CommandDefinitionPtr(new command::ReConnectDefinition));

    commandParser_->registerMatcher(std::move(std::unique_ptr<ICommandMatcher>(new AbsoluteCommandMatcher)));
    commandParser_->registerMatcher(std::move(std::unique_ptr<ICommandMatcher>(new PatternCommandMatcher)));
  }

  DescriptorCommandQueue::~DescriptorCommandQueue() {
  }

  bool DescriptorCommandQueue::loop(IGameInstance* gameInstance,
                                    QueueObjectQueue *discard) {
    while (!queue_.empty()) {
      std::shared_ptr<QueueObject> object = queue_.front();
      queue_.pop();

      std::shared_ptr<ICommandDefinition> def;

      if (commandParser_->matchCommand(object->originalString, def)) {
        if (def == NULL) {
          if (discard != NULL) {
            discard->push(object);
          }
        } else {
          std::unique_ptr<ICommand> cmd = def->factory();
          std::shared_ptr<CommandScope> scope(new CommandScope());
          scope->queueObject = object;
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

  bool DescriptorCommandQueue::addQueueObject(std::shared_ptr<QueueObject> object) {
    queue_.push(object);
    return true;
  }

}  // namespace omush
