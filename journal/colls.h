#ifndef JOURNAL_COLLS_H
#define JOURNAL_COLLS_H

#include "models.h"
#include "shot/DbClient.h"

namespace journal {
  

class Collection {
public:
  static int const COUNT_PER_PAGE = 16;

  Collection(shot::DbClient* db, char const* table);
  void genId(Journal& journal, std::ostream& updates);
  void genSlug(Journal& journal, std::ostream& updates);
  void genTags(Journal& journal, std::ostream& updates);
  JournalPtr get(string& id);
  JournalPtr getBySlug(string& slug);
  void update(string& id, Journal& journal, ostream& updates);
  void append(Journal& journal, ostream& updates);
  void remove(string& id);
  int query(int page, std::ostream& out);

  shot::DbClient* db;
  char const* table;
};


class ItemsCollection {
public:
  ItemsCollection(shot::DbClient* db, char const* table);
  void genId(Node& node, std::ostream& updates);
  NodePtr get(string& id);
  void update(string& id, Node& node, ostream& updates);
  void append(Node& node, ostream& updates);
  void remove(string& id);
  int queryPageItems(std::string pageId, ostream& out);

  shot::DbClient* db;
  char const* table;
};


class Document {
public:
  Document(shot::DbClient* db, char const* table);
  void update(string& params, ostream& updates);

  shot::DbClient* db;
  char const* table;
};


int itemsCursorToStream(mongo::DBClientCursor& cursor, std::ostream& stream);
Node* createNode(NodeType nodeType);


} /* namespace journal */


#endif /* end of include guard: JOURNAL_COLLS_H */
