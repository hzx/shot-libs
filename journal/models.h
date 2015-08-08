#ifndef JOURNAL_MODELS_H
#define JOURNAL_MODELS_H

#include <string>
#include <vector>
#include <memory>
#include "shot/Model.h"
#include "shot/values.h"

using std::string;
using std::vector;
using std::unique_ptr;
using namespace bson;
using shot::Int;
using shot::Float;
using shot::String;

namespace journal {


class Node;


enum NodeType {
  NT_NONE = 0,
  NT_BLOCK,
  NT_H1,
  NT_H2,
  NT_TEXT,
  NT_CODE,
  NT_LINK,
  NT_VIDEO,
  NT_GOOGLE_MAP,
  NT_FILE,
  NT_IMAGE,
  NT_GALLERY,
  NT_BIG_SLIDER,
  NT_MINI_SLIDER,
};


class Journal {
public:
  String id;
  String name;
  String slug;
  vector<string> items;
};
typedef std::unique_ptr<Journal> JournalPtr;


class JournalItems {
public:
  ~JournalItems();
  vector<Node*> nodes;
};
  

class Props {
public:
};


class Node {
public:
  String id;
  int code;
  Props props;
};


class Block: public Node {
public:
  Block();
  ~Block();
  vector<Node*> nodes;
};


class Code: public Node {
public:
  Code();
  String value;
};


class Text: public Node {
public:
  Text();
  String value;
};


class Header1: public Node {
public:
  Header1();
  String value;
};


class Header2: public Header1 {
public:
  Header2();
};


class Link: public Node {
public:
  Link();
  String source;
  String text;
};


class Video: public Node {
public:
  Video();
  String source;
};


class GoogleMap: public Node {
public:
  GoogleMap();
  Int zoom;
  Float lat;
  Float lng;
  String icon;
};


class File: public Node {
public:
  File();
  String filename;
  String text;
};


class Image: public Node {
public:
  Image();
  String filename;
};


class Gallery: public Node {
public:
  Gallery();
  vector<string> images;
};

class BigSlider: public Node {
public:
  BigSlider();
  vector<string> images;
};

class MiniSlider: public Node {
public:
  MiniSlider();
  vector<string> images;
};


/* class JournalModel { */
/* public: */
/*   String id; */
/*   String name; */
/*   vector<string> items; */
/* }; */
/* typedef unique_ptr<JournalModel> JournalPtr; */


/* class CodeModel { */
/* public: */
/*   String id; */
/*   String text; */
/* }; */
/* typedef unique_ptr<CodeModel> CodePtr; */


/* class FileModel { */
/* public: */
/*   String id; */
/*   String filename; */
/* }; */
/* typedef unique_ptr<FileModel> FilePtr; */


/* class GalleryModel { */
/* public: */
/*   String id; */
/*   vector<string> images; */
/* }; */
/* typedef unique_ptr<GalleryModel> GalleryPtr; */


/* class GoogleMapModel { */
/* public: */
/*   String id; */
/* }; */
/* typedef unique_ptr<GoogleMapModel> GoogleMapPtr; */


/* class HeaderModel { */
/* public: */
/*   String id; */
/* }; */
/* typedef unique_ptr<HeaderModel> HeaderPtr; */


/* class ImageModel { */
/* public: */
/*   String id; */
/* }; */
/* typedef unique_ptr<ImageModel> ImagePtr; */


/* class LinkModel { */
/* public: */
/*   String id; */
/* }; */
/* typedef unique_ptr<LinkModel> LinkPtr; */


/* class TextModel { */
/* public: */
/*   String id; */
/* }; */
/* typedef unique_ptr<TextModel> TextPtr; */


/* class VideoModel { */
/* public: */
/*   String id; */
/* }; */
/* typedef unique_ptr<VideoModel> VideoPtr; */


} /* namespace journal */


#endif /* end of include guard: JOURNAL_MODELS_H */
