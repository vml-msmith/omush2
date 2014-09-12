/**
 * \file help.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/help/help.h"

namespace omush {
  bool HelpSystem::getHelpByIndex(std::string index,
                                  std::shared_ptr<HelpEntry> &entry) {
      entry = nullptr;

      if (getHelpByIndexInDirectory(index, entry)) {
        return true;
      }

      // Look it up in the DB.
      if (!HelpDb::find(index, entry)) {
        return false;
      }

      // Found it, add it to the directory and the LLNode.
      addItemToDirectory(index, entry);

      return true;
  }

  bool HelpSystem::addItemToDirectory(std::string index,
                                      std::shared_ptr<HelpEntry> &entry) {
    if (directory_.size() > maxItems) { // Above max.
      popFromBack();
    }

    std::shared_ptr<HelpLLNode> node(new HelpLLNode());
    node->entry = entry;
    node->next = nullptr;
    node->prev = nullptr;
    node->key = index;

    if (llTop_ == nullptr) {
      llTop_ = node;
    }

    if (llEnd_ == nullptr) {
      llEnd_ = nullptr;
    }
    else {
      llEnd_->next = node;
      node->prev = llEnd_;
    }

    directory_.insert(std::pair<std::string,
                      std::shared_ptr<HelpLLNode>>(index, node));
    return true;
  }

  bool HelpSystem::popFromBack() {
    if (llEnd_ == NULL) {
      return true;
    }

    std::shared_ptr<HelpLLNode> node = llEnd_;
    llEnd_ = node->prev;
    if (node->prev != NULL) {
      node->prev->next = NULL;
    }
    directory_.erase(node->key);
    return true;
  }

  bool HelpSystem::moveToFront(std::shared_ptr<HelpLLNode> node) {
    if (node == llTop_)
      return true;

    if (node->prev != NULL) {
      node->prev->next = node->next;
    }

    if (node->next != NULL) {
      node->next->prev = node->prev;
    }

    if (node == llEnd_) {
      llEnd_ = node->prev;
    }

    node->prev = NULL;
    node->next = llTop_;
    llTop_->prev = node;
    llTop_ = node;
    return true;
  }

  bool HelpSystem::getHelpByIndexInDirectory(std::string index,
                                             std::shared_ptr<HelpEntry> &entry) {
    StringToHelpLLNodeMap::iterator iter = directory_.find(index);
    if (iter == directory_.end()) {
      return false;
    }

    // Move it to the front.
    entry = iter->second->entry;
    moveToFront(iter->second);
    return true;
  }

  std::shared_ptr<HelpSystem> MyHelp::getInstance(std::string key) {
    return MyHelp::getSelfInstance()._getInstance(key);
  }

  std::shared_ptr<HelpSystem> MyHelp::_getInstance(std::string key) {
    if (directory_.find(key) == directory_.end())
      return nullptr;

    return directory_.find(key)->second;
  }

  std::shared_ptr<HelpSystem> MyHelp::startInstance(std::string key) {
    return MyHelp::getSelfInstance()._startInstance(key);
  }

  std::shared_ptr<HelpSystem> MyHelp::_startInstance(std::string key) {
    if (directory_.find(key) == directory_.end()) {
      std::shared_ptr<HelpSystem> h(new HelpSystem);
      directory_.insert(std::pair<std::string,
                        std::shared_ptr<HelpSystem>>(key,
                                                     h));
    }

    return directory_.find(key)->second;
  }
}  // namespace omush
