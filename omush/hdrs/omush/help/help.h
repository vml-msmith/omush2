/**
 * \file help.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_HELP_HELP_H_
#define OMUSH_HDRS_OMUSH_HELP_HELP_H

#include <string>
#include <map>
#include <memory>

namespace omush {

  class HelpEntry {

  };

  struct HelpLLNode {
    std::shared_ptr<HelpEntry> entry;
    std::shared_ptr<HelpLLNode> next;
    std::shared_ptr<HelpLLNode> prev;
    std::string key;
  };

  class HelpDb {
  public:
    static bool find(std::string, std::shared_ptr<HelpEntry>) {
      return true;
    }

  };

  class HelpSystem {
   public:
    typedef std::string HelpIndexString;
    bool getHelpByIndex(HelpIndexString index, std::shared_ptr<HelpEntry> &entry);

   private:
    int maxItems = 10;

    bool getHelpByIndexInDirectory(std::string, std::shared_ptr<HelpEntry> &entry);
    bool popFromBack();
    bool moveToFront(HelpLLNode* node);
    bool addItemToDirectory(std::string index, std::shared_ptr<HelpEntry> &entry);

    std::shared_ptr<HelpLLNode> llTop_;
    std::shared_ptr<HelpLLNode> llEnd_;

    typedef std::map<std::string, std::shared_ptr<HelpLLNode>> StringToHelpLLNodeMap;
    StringToHelpLLNodeMap directory_;
  };

}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_HELP_HELP_H
