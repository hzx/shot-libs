#include "models.h"


namespace session {


std::string const FileModel::S_NAME = std::to_string(FileModel::NAME);
std::string const FileModel::S_FILENAME = std::to_string(FileModel::FILENAME);
std::string const FileModel::S_DATE = std::to_string(FileModel::DATE);
std::string const FileModel::S_BUNCH_ID = std::to_string(FileModel::BUNCH_ID);


int FileModel::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(S_NAME)) name.set(obj.getField(S_NAME).String());
  if (obj.hasField(S_FILENAME)) filename.set(obj.getField(S_FILENAME).String());
  if (obj.hasField(S_DATE)) date.set(obj.getField(S_DATE).Date().toTimeT());
  if (obj.hasField(S_BUNCH_ID)) bunchId.set(obj.getField(S_BUNCH_ID).String());
}


int FileModel::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case NAME:
      name.set(value);
      break;
    case FILENAME:
      filename.set(value);
      break;
    case DATE:
      date.set(value);
      break;
    case BUNCH_ID:
      bunchId.set(value);
      break;
  }
}


void FileModel::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (name.has) builder << S_NAME << name.value;
  if (filename.has) builder << S_FILENAME << filename.value;
  if (date.has) builder << S_DATE << mongo::Date_t(date.value);
  if (bunchId.has) builder << S_BUNCH_ID << bunchId.value;
}


void FileModel::toCompactFormat(ostream& stream) {
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (name.has) stream << S_NAME << DF << name.value << DF;
  if (filename.has) stream << S_FILENAME << DF << filename.value << DF;
  if (date.has) stream << S_DATE << DF << date.value << DF;
  if (bunchId.has) stream << S_BUNCH_ID << DF << bunchId.value << DF;
}

  
} /* namespace session */
