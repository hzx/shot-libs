#include "colls.h"
#include "shot/utils.h"
#include "shot/translit.h"

namespace journal {
  

Collection::Collection(shot::DbClient* db, char const* table) {
  this->db = db;
  this->table = table;
}


void Collection::genId(Journal& journal, std::ostream& updates) {
  std::string id = shot::newId();
  journal.id.set(id);
  updates << shot::ID << DF << id << DF;
}


void Collection::genSlug(Journal& journal, std::ostream& updates) {
  auto slug = shot::slugify(journal.name.value);
  journal.slug.set(slug);
  updates << Journal::S_SLUG << DF << slug << DF;
}


void Collection::genTags(Journal& journal, std::ostream& updates) {
}


JournalPtr Collection::get(string& id) {
  if (id.length() < shot::OID_SIZE) return nullptr;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return nullptr;

  JournalPtr journal(new Journal());
  journal->fromDbFormat(obj);

  return journal;
}


JournalPtr Collection::getBySlug(string& slug) {
  bson::bo obj = db->conn.findOne(table, BSON(Journal::S_SLUG << slug));
  if (obj.isEmpty()) return nullptr;

  JournalPtr journal(new Journal());
  journal->fromDbFormat(obj);

  return journal;
}


void Collection::update(string& id, Journal& journal, ostream& updates) {
  if (journal.name.has) {
    genSlug(journal, updates);
    genTags(journal, updates);
  }

  bson::bob builder;

  journal.toDbFormat(builder);
  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}


void Collection::append(Journal& journal, ostream& updates) {
  if (journal.id.value.length() < shot::OID_SIZE) genId(journal, updates);
  genSlug(journal, updates);
  genTags(journal, updates);

  bson::bob builder;

  journal.toDbFormat(builder);
  db->conn.insert(table, builder.obj());
}


void Collection::remove(string& id) {
  if (id.length() < shot::OID_SIZE) return;

  db->conn.remove(table, BSON(shot::S_ID << mongo::OID(id)));
}


int Collection::query(int page, std::ostream& out) {
  auto cursor = db->conn.query(table, bson::bo());
  return shot::cursorToStream<Journal>(*cursor, out).limit(COUNT_PER_PAGE);
}


ItemsCollection::ItemsCollection(shot::DbClient* db, char const* table) {
  this->db = db;
  this->table = table;
}


void ItemsCollection::genId(Node& node, std::ostream& updates) {
}


NodePtr ItemsCollection::get(string& id) {
  return nullptr;
}


void ItemsCollection::update(string& id, Node& node, ostream& updates) {
}


void ItemsCollection::append(Node& node, ostream& updates) {
}


void ItemsCollection::remove(string& id) {
}


Document::Document(shot::DbClient* db, char const* table) {
  this->db = db;
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
