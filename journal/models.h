#ifndef JOURNAL_MODELS_H
#define JOURNAL_MODELS_H

#include <string>
#include <vector>
#include <memory>
#include "shot/Model.h"
#include "shot/values.h"


namespace journal {


char const DF = shot::DELIM_FIELD;
char const DR = shot::DELIM_ROW;
class Node;


enum class NodeType {
  None = 0,
  Block,
  H1,
  H2,
  Text,
  Code,
  Link,
  Video,
  GoogleMap,
  File,
  Image,
  Gallery,
  BigSlider,
  MiniSlider,
  Anchor,
  Break,
};


class Journal: public shot::Model {
public:
  static int const NAME = 2;
  static int const SLUG = 3;
  static int const KEYWORDS = 4;
  static int const DESCRIPTION = 5;
  static int const SHOW = 6;
  static int const ITEMS = 7;
  static int const TAGS = 8;

  static std::string const S_NAME;
  static std::string const S_SLUG;
  static std::string const S_KEYWORDS;
  static std::string const S_DESCRIPTION;
  static std::string const S_SHOW;
  static std::string const S_ITEMS;
  static std::string const S_TAGS;

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);

  shot::String id;
  shot::String name;
  shot::String slug;
  shot::String keywords;
  shot::String description;
  shot::Bool show;
  std::vector<std::string> items;
  std::vector<std::string> tags;
};
typedef std::unique_ptr<Journal> JournalPtr;


class JournalItems {
public:
  ~JournalItems();
  std::vector<Node*> nodes;
};
  

class Node {
public:
  static int const TYPE = 2;
  static int const PAGE_ID = 3;
  static int const STYLE = 4;

  static std::string const S_TYPE;
  static std::string const S_PAGE_ID;
  static std::string const S_STYLE;

  NodeType nodeType;
  shot::String id;
  shot::String pageId;
  shot::String style;

  virtual int fromDbFormat(bson::bo& obj) = 0;
  virtual int parseField(int code, std::string const& value) = 0;
  virtual void toDbFormat(bson::bob& builder) = 0;
  virtual void toCompactFormat(ostream& stream) = 0;
};
typedef std::unique_ptr<Node> NodePtr;


class Block: public Node {
public:
  std::vector<Node*> nodes;

  Block();
  ~Block();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class Header1: public Node {
public:
  Header1();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class Header2: public Node {
public:
  static int const TEXT = 5;

  static std::string const S_TEXT;

  shot::String text;

  Header2();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class Text: public Node {
public:
  static int const TEXT = 5;

  static std::string const S_TEXT;

  shot::String text;

  Text();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class Code: public Node {
public:
  static int const TEXT = 5;

  static std::string const S_TEXT;

  shot::String text;

  Code();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class Link: public Node {
public:
  static int const SRC = 5;
  static int const ALT = 6;

  static std::string const S_SRC;
  static std::string const S_ALT;

  shot::String src;
  shot::String alt;

  Link();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class Video: public Node {
public:
  static int const TEXT = 5;

  static std::string const S_TEXT;

  shot::String text;

  Video();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class GoogleMap: public Node {
public:
  static int const ZOOM = 5;
  static int const LAT = 6;
  static int const LNG = 7;

  static std::string const S_ZOOM;
  static std::string const S_LAT;
  static std::string const S_LNG;

  shot::Int zoom;
  shot::Float lat;
  shot::Float lng;
  /* shot::String icon; */
  
  GoogleMap();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class File: public Node {
public:
  static int const FILENAME = 5;
  static int const TEXT = 6;

  static std::string const S_FILENAME;
  static std::string const S_TEXT;

  shot::String filename;
  shot::String text;

  File();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class Image: public Node {
public:
  static int const FILENAME = 5;

  static std::string const S_FILENAME;

  shot::String filename;

  Image();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class Gallery: public Node {
public:
  static int const IMAGES = 5;

  static std::string const S_IMAGES;

  std::vector<std::string> images;

  Gallery();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class BigSlider: public Node {
public:
  static int const IMAGES = 5;

  static std::string const S_IMAGES;

  std::vector<std::string> images;

  BigSlider();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class MiniSlider: public Node {
public:
  static int const IMAGES = 5;

  static std::string const S_IMAGES;

  std::vector<std::string> images;

  MiniSlider();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class Anchor: public Node {
public:
  static int const NAME = 5;

  static std::string const S_NAME;

  shot::String name;

  Anchor();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


class Break: public Node {
public:
  Break();

  int fromDbFormat(bson::bo& obj);
  int parseField(int code, std::string const& value);
  void toDbFormat(bson::bob& builder);
  void toCompactFormat(ostream& stream);
};


/* class JournalModel { */
/* public: */
/*   shot::String id; */
/*   shot::String name; */
/*   std::vector<std::string> items; */
/* }; */
/* typedef std::unique_ptr<JournalModel> JournalPtr; */


/* class CodeModel { */
/* public: */
/*   shot::String id; */
/*   shot::String text; */
/* }; */
/* typedef std::unique_ptr<CodeModel> CodePtr; */


/* class FileModel { */
/* public: */
/*   shot::String id; */
/*   shot::String filename; */
/* }; */
/* typedef std::unique_ptr<FileModel> FilePtr; */


/* class GalleryModel { */
/* public: */
/*   shot::String id; */
/*   std::vector<std::string> images; */
/* }; */
/* typedef std::unique_ptr<GalleryModel> GalleryPtr; */


/* class GoogleMapModel { */
/* public: */
/*   shot::String id; */
/* }; */
/* typedef std::unique_ptr<GoogleMapModel> GoogleMapPtr; */


/* class HeaderModel { */
/* public: */
/*   shot::String id; */
/* }; */
/* typedef std::unique_ptr<HeaderModel> HeaderPtr; */


/* class ImageModel { */
/* public: */
/*   shot::String id; */
/* }; */
/* typedef std::unique_ptr<ImageModel> ImagePtr; */


/* class LinkModel { */
/* public: */
/*   shot::String id; */
/* }; */
/* typedef std::unique_ptr<LinkModel> LinkPtr; */


/* class TextModel { */
/* public: */
/*   shot::String id; */
/* }; */
/* typedef std::unique_ptr<TextModel> TextPtr; */


/* class VideoModel { */
/* public: */
/*   shot::String id; */
/* }; */
/* typedef std::unique_ptr<VideoModel> VideoPtr; */


} /* namespace journal */


#endif /* end of include guard: JOURNAL_MODELS_H */
