#include "colls.h"
#include "shot/utils.h"

namespace journal {
  

Collection::Collection(char const* table) {
  this->table = table;
}


JournalPtr Collection::get(string& id) {
  return nullptr;
}


JournalPtr Collection::getBySlug(string& slug) {
  return nullptr;
}


void Collection::update(string& id, Journal& journal, ostream& updates) {
}


void Collection::append(Journal& journal, ostream& updates) {
}


void Collection::remove(string& id) {
}


Document::Document(char const* table) {
  this->table = table;
}


void Document::update(string& params, ostream& updates) {
  // split rows
  auto rows = shot::parseRows(params);
  for (int i = 0; i < rows.size(); ++i) {
    auto fields = shot::parseFields(rows[i]);
  }
}


} /* namespace journal */
