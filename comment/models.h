#ifndef COMMENT_MODELS_H
#define COMMENT_MODELS_H


#include <string>
#include <vector>
#include <memory>
#include "shot/Model.h"
#include "shot/values.h"

  
namespace comment {


char const DF = shot::DELIM_FIELD;
char const DR = shot::DELIM_ROW;


class Comment: public shot::Model {
public:
  static int const PARENT_ID = 2;
  static int const USER_ID = 3;
  static int const TEXT = 4;
  static int const STATE = 5;

  static std::string const S_PARENT_ID;
  static std::string const S_USER_ID;
  static std::string const S_TEXT;
  static std::string const S_STATE;

  static int const STATE_NEW = 1;
  static int const STATE_MODERATE = 2;
  static int const STATE_BAN = 3;

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);

  shot::String id;
  shot::String parentId;
  shot::String userId;
  shot::String text;
  shot::Int state;
};
typedef std::unique_ptr<Comment> CommentPtr;


} /* namespace comment */


#endif /* end of include guard: COMMENT_MODELS_H */
