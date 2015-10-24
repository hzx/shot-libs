#ifndef SESSION_COLLECTIONS_H
#define SESSION_COLLECTIONS_H


#include <string>
#include <ostream>
#include "shot/DbClient.h"
#include "models.h"


namespace session {


class FileCollection {
public:
  static void genId(FileModel& file, std::ostream& updates);

  FileCollection(shot::DbClient* db, char const* table, std::string& dir);
  void appendRaw(std::string& obj, std::ostream& updates);
  FilePtr get(std::string& id);
  FilePtr getByName(std::string& name);
  void updateRaw(std::string& id, std::string& params, std::ostream& updates);
  void remove(std::string& id);
  void removeWithFile(std::string& id);

  shot::DbClient* db;
  char const* table;
  std::string dir;
};

  
} /* namespace session */

#endif /* end of include guard: SESSION_COLLECTIONS_H */
