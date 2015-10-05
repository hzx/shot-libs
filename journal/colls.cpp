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
  // TODO: push paging here in query

  auto cursor = db->conn.query(table, mongo::Query().sort(shot::S_ID, -1), COUNT_PER_PAGE);
  return shot::cursorToStream<Journal>(*cursor, out);
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


int ItemsCollection::queryPageItems(std::string pageId, ostream& out) {
  if (pageId.size() < shot::OID_SIZE) return 0;

  auto cursor = db->conn.query(table, BSON(Node::S_PAGE_ID << mongo::OID(pageId)));
  return itemsCursorToStream(*cursor, out);
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


int itemsCursorToStream(mongo::DBClientCursor& cursor, std::ostream& stream) {
  int counter = 0;

  while (cursor.more()) {
    ++counter;
    bson::bo obj = cursor.next();
    std::unique_ptr<Node> node;

    if (obj.hasField(Node::S_TYPE)) {
      int nodeType = obj.getField(Node::S_TYPE).Int();
      node.reset(createNode(static_cast<NodeType>(nodeType)));
      if (node.get() == nullptr) continue;
    }

    node->fromDbFormat(obj);
    node->toCompactFormat(stream);

    stream << shot::DELIM_ROW;
  }

  return counter;
}


Node* createNode(NodeType nodeType) {
  switch (nodeType) {
    case NodeType::H1:
      return new Header1();
    case NodeType::H2:
      return new Header2();
    case NodeType::Text:
      return new Text();
    case NodeType::Code:
      return new Code();
    case NodeType::Link:
      return new Link();
    case NodeType::Video:
      return new Video();
    case NodeType::GoogleMap:
      return new GoogleMap();
    case NodeType::File:
      return new File();
    case NodeType::Image:
      return new Image();
    case NodeType::Gallery:
      return new Gallery();
    case NodeType::BigSlider:
      return new BigSlider();
    case NodeType::MiniSlider:
      return new MiniSlider();
    case NodeType::Anchor:
      return new Anchor();
    case NodeType::Break:
      return new Break();
  }

  return nullptr;
}


} /* namespace journal */
