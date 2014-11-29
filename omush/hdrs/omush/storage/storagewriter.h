/**
 * \file storagewriter.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_STORAGE_STORAGEWRITER_H_
#define OMUSH_HDRS_OMUSH_STORAGE_STORAGEWRITER_H_

#include <sqlite3.h>

namespace omush {
  namespace storage {
    class StorageWriter {
     public:
      StorageWriter();
      bool openFile(std::string fileName) {
        if (isOpen_) {
          // TODO(msmith) Log this. Need to close before we can open.
          return false;
        }

        fileName_ = fileName;
        int error;
        error = sqlite3_open(fileName.c_str(), &dbFile_);
        if (error) {
          // TODO(msmith) Log this. sqlite3_errmsg(db). May even create a method for it.
          return false;
        }
        else {
          isOpen_ = true;
          return true;
        }
      }

      bool closeFile() {
        if (isOpen_) {
          sqlite3_close(dbFile_);
        }

        return true;
      }

      void createTables() {
        if (!isOpen_)
          return;

        std::vector<std::string> sqls;

        sqls.push_back("CREATE TABLE REBOOT("          \
                       "ID INT PRIMARY KEY  AUTOINCREMENT   NOT NULL,"   \
                       "REBOOTID TEXT NOT NULL);");

        sqls.push_back("CREATE TABLE CONNECTIONS("       \
                       "REBOOT_ID       INT     NOT NULL," \
                       "DB_ID TEXT NOT NULL," \
                       "CONNECT_TIME           TEXT    NOT NULL," \
                       "LAST_ACTIVE_TIME           TEXT    NOT NULL,"              \
                       "FOREIGN KEY(OBJECTID) REFERENCES REBOOT(ID));");

        for (int i = 0; i < sqls.size(); ++i) {
          statement(sqls[i]);
        }
      }
     private:
      std::string fileName_;
      bool isOpen_;
      sqlite3 *dbFile_;
    };
  }  // namespace storage
}  // namespace omush
#endif  // OMUSH_HDRS_OMUSH_STORAGE_STORAGEWRITER_H_
