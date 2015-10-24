#include "collections.h"
#include "shot/utils.h"


namespace session {


void FileCollection::genId(FileModel& file, std::ostream& updates) {
  std::string id = shot::newId();
  file.id.set(id);
  updates << shot::ID << DF << id << DF;
}


FileCollection::FileCollection(shot::DbClient* db, char const* table,
    std::string& dir) {
  this->db = db;
  this->table = table;
  this->dir = dir;
}


void FileCollection::appendRaw(std::string& obj, std::ostream& updates) {
  bson::bob builder;
  FileModel file;

  file.fromCompactFormat(obj);
  if (file.id.value.length() < shot::OID_SIZE) genId(file, updates);
  file.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}


FilePtr FileCollection::get(std::string& id) {
  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return nullptr;

  FilePtr file(new FileModel());
  file->fromDbFormat(obj);

  return file;
}


FilePtr FileCollection::getByName(std::string& name) {
  bson::bo obj = db->conn.findOne(table, BSON(FileModel::S_NAME << name));
  if (obj.isEmpty()) return nullptr;

  FilePtr file(new FileModel());
  file->fromDbFormat(obj);

  return file;
}


void FileCollection::updateRaw(std::string& id, std::string& params, std::ostream& updates) {
  // do nothing
}


void FileCollection::remove(std::string& id) {
  if (id.length() != shot::OID_SIZE) return;

  db->conn.remove(table, BSON(shot::S_ID << mongo::OID(id)));
}


void FileCollection::removeWithFile(std::string& id) {
  auto file = get(id);
  if (file.get() == nullptr) return;

  std::string fullname = dir + file->name.value;
  if (fullname.length() > dir.length()) {
    shot::rm(fullname);
  }

  db->conn.remove(table, BSON(shot::S_ID << mongo::OID(id)));
}

  
} /* namespace session */
