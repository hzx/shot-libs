#ifndef COMMENT_COLLECTIONS_H
#define COMMENT_COLLECTIONS_H

#include <string>
#include <ostream>
#include "shot/DbClient.h"
#include "models.h"

namespace comment {


class Collection {
public:
  static void genId(Comment& comment, std::ostream& updates);

  Collection(shot::DbClient* db, char const* table);
  void appendRaw(std::string& obj, std::ostream& updates);
  CommentPtr get(std::string& id);
  void updateRaw(std::string& id, std::string& params, std::ostream& updates);
  void remove(std::string& id);

  shot::DbClient* db;
  char const* table;
};

  
} /* namespace comment */

#endif /* end of include guard: COMMENT_COLLECTIONS_H */
