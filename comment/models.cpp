#include "models.h"


namespace comment {


std::string const Comment::S_PARENT_ID = std::to_string(Comment::PARENT_ID);
std::string const Comment::S_USER_ID = std::to_string(Comment::USER_ID);
std::string const Comment::S_TEXT = std::to_string(Comment::TEXT);
std::string const Comment::S_STATE = std::to_string(Comment::STATE);


int Comment::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(S_PARENT_ID)) parentId.set(obj.getField(S_PARENT_ID).OID().toString());
  if (obj.hasField(S_USER_ID)) userId.set(obj.getField(S_USER_ID).OID().toString());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());
  if (obj.hasField(S_STATE)) state.set(obj.getField(S_STATE).Int());

  return 0;
}

int Comment::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case PARENT_ID:
      parentId.set(value);
      break;
    case USER_ID:
      userId.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
    case STATE:
      try {
        state.set(std::stoi(value));
      } catch (...) {
      }
      break;
  }

  return 0;
}

void Comment::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (parentId.has) builder << S_PARENT_ID << mongo::OID(parentId.value);
  if (userId.has) builder << S_USER_ID << mongo::OID(userId.value);
  if (text.has) builder << S_TEXT << text.value;
  if (state.has) builder << S_STATE << state.value;
}

void Comment::toCompactFormat(ostream& stream) {
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (parentId.has) stream << S_PARENT_ID << DF << parentId.value << DF;
  if (userId.has) stream << S_USER_ID << DF << userId.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
  if (state.has) stream << S_STATE << DF << state.value << DF;
}

  
} /* namespace comment */
