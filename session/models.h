#ifndef SESSION_MODELS_H
#define SESSION_MODELS_H


#include <string>
#include <vector>
#include <memory>
#include "shot/Model.h"
#include "shot/values.h"


namespace session {


char const DF = shot::DELIM_FIELD;
char const DR = shot::DELIM_ROW;


class FileModel: public shot::Model {
public:
  static int const NAME = 2;
  static int const FILENAME = 3;
  static int const DATE = 4;
  static int const BUNCH_ID = 5;;

  static std::string const S_NAME;
  static std::string const S_FILENAME;
  static std::string const S_DATE;
  static std::string const S_BUNCH_ID;

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);

  shot::String id;
  shot::String name;
  shot::String filename;
  shot::Uint date;
  shot::String bunchId;
};
typedef std::unique_ptr<FileModel> FilePtr;

  
} /* namespace session */

#endif /* end of include guard: SESSION_MODELS_H */
