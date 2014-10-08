/**
 * \file help.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_HELP_HELP_H_
#define OMUSH_HDRS_OMUSH_HELP_HELP_H_

#include <string>
#include <map>
#include <memory>
#include "omush/library/string.h"

namespace omush {

  class HelpEntry {
  public:
    std::string details;
    std::string index;
  };

  struct HelpLLNode {
   public:
    std::shared_ptr<HelpEntry> entry;
    std::shared_ptr<HelpLLNode> next;
    std::shared_ptr<HelpLLNode> prev;
    std::string key;
  };

  class HelpDb {
   public:
    static bool find(std::string key, std::shared_ptr<HelpEntry> &entry) {
      bool found = false;
      std::string index = "";
      std::string details = "";
      if (library::string::iequals(key, "") || library::string::iequals(key, "") || library::string::iequals(key, "help")) {
        found = true;
        index = "Help";
        details = "These are the help files.";
      }
      else if (library::string::iequals(key, "commands")) {
        found = true;
        index = "Commands";
        details = "These are the commands.";
      }
      else {
        printf(std::string("Not found: " + key  +"\n").c_str());
      }

      if (found) {
        entry = std::shared_ptr<HelpEntry>(new HelpEntry);
        entry->details = details;
        entry->index = index;
        printf("Found it not cached.\n");
        return true;
      }

      entry = nullptr;
      return false;
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
    bool moveToFront(std::shared_ptr<HelpLLNode> node);
    bool addItemToDirectory(std::string index, std::shared_ptr<HelpEntry> &entry);

    std::shared_ptr<HelpLLNode> llTop_;
    std::shared_ptr<HelpLLNode> llEnd_;

    typedef std::map<std::string, std::shared_ptr<HelpLLNode>> StringToHelpLLNodeMap;
    StringToHelpLLNodeMap directory_;
  };

  class MyHelp {
   public:
    static std::shared_ptr<HelpSystem> getInstance(std::string key);
    static std::shared_ptr<HelpSystem> startInstance(std::string key);
    static MyHelp& getSelfInstance() {
            static MyHelp    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
    }
    std::shared_ptr<HelpSystem> _getInstance(std::string key);
    std::shared_ptr<HelpSystem> _startInstance(std::string key);
   private:
    MyHelp(MyHelp const&);              // Don't Implement
    void operator=(MyHelp const&); // Don't implement
    MyHelp() {
    }
    ~MyHelp() {}
    std::map<std::string,std::shared_ptr<HelpSystem>> directory_;
  };

}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_HELP_HELP_H_
