#ifndef JOURNAL_COLLS_H
#define JOURNAL_COLLS_H

#include "models.h"

namespace journal {
  

class Collection {
public:
  Collection(char const* table);
  JournalPtr get(string& id);
  JournalPtr getBySlug(string& slug);
  void update(string& id, Journal& journal, ostream& updates);
  void append(Journal& journal, ostream& updates);
  void remove(string& id);

  char const* table;
};


class Document {
public:
  Document(char const* table);
  void update(string& params, ostream& updates);

  char const* table;
};


} /* namespace journal */


#endif /* end of include guard: JOURNAL_COLLS_H */
