#include "collections.h"

namespace comment {


void Collection::genId(Comment& comment, std::ostream& updates) {
  std::string id = shot::newId();
  comment.id.set(id);
  updates << shot::ID << DF << id << DF;
}

Collection::Collection(shot::DbClient* db, char const* table) {
  this->db = db;
  this->table = table;
}

void Collection::appendRaw(std::string& obj, std::ostream& updates) {
  Comment comment;
  bson::bob builder;

  comment.fromCompactFormat(obj);
  if (comment.id.value.length() < shot::OID_SIZE) genId(comment, updates);
  comment.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

CommentPtr Collection::get(std::string& id) {
  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return nullptr;

  CommentPtr comment(new Comment());

  comment->fromDbFormat(obj);

  return comment;
}

void Collection::updateRaw(std::string& id, std::string& params,
    std::ostream& updates) {
  Comment comment;
  bson::bob builder;

  comment.fromCompactFormat(params);
  comment.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void Collection::remove(std::string& id) {
  if (id.length() < shot::OID_SIZE) return;

  db->conn.remove(table, BSON(shot::S_ID << mongo::OID(id)));
}


} /* namespace comment */
