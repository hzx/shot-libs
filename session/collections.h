#ifndef SESSION_COLLECTIONS_H
#define SESSION_COLLECTIONS_H


#include <string>
#include <ostream>
#include "shot/DbClient.h"
#include "models.h"


namespace session {


class FileCollection {
public:
  static void genId(FileModel& file);

  FileCollection(shot::DbClient* db, char const* table);
  void append(FileModel& file);
  FilePtr get(std::string& id);
  FilePtr getByName(std::string& name);
  void updateRaw(std::string& id, std::string& params);
  void remove(std::string& id);
  void removeWithFile(std::string& id);

  shot::DbClient* db;
  char const* table;
  std::string dir;
};

  
} /* namespace session */

#endif /* end of include guard: SESSION_COLLECTIONS_H */
