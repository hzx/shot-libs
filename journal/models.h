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
  shot::String id;
  NodeType code;
  shot::String styleClass;
  shot::String padding;
  shot::String margin;
};
typedef std::unique_ptr<Node> NodePtr;


class Block: public Node {
public:
  Block();
  ~Block();
  std::vector<Node*> nodes;
};


class Code: public Node {
public:
  Code();
  shot::String value;
};


class Text: public Node {
public:
  Text();
  shot::String value;
};


class Header1: public Node {
public:
  Header1();
  shot::String value;
};


class Header2: public Header1 {
public:
  Header2();
};


class Link: public Node {
public:
  Link();
  shot::String source;
  shot::String text;
};


class Video: public Node {
public:
  Video();
  shot::String source;
};


class GoogleMap: public Node {
public:
  GoogleMap();
  shot::Int zoom;
  shot::Float lat;
  shot::Float lng;
  shot::String icon;
};


class File: public Node {
public:
  File();
  shot::String filename;
  shot::String text;
};


class Image: public Node {
public:
  Image();
  shot::String filename;
};


class Gallery: public Node {
public:
  Gallery();
  std::vector<std::string> images;
};


class BigSlider: public Node {
public:
  BigSlider();
  std::vector<std::string> images;
};


class MiniSlider: public Node {
public:
  MiniSlider();
  std::vector<std::string> images;
};


class Anchor: public Node {
public:
  Anchor();
  shot::String name;
};


class Break: public Node {
public:
  Break();
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
