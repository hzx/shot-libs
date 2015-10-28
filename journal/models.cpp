#include "models.h"
#include "shot/utils.h"
#include "shot/translit.h"


namespace journal {


std::string const Journal::S_NAME = std::to_string(Journal::NAME);
std::string const Journal::S_SLUG = std::to_string(Journal::SLUG);
std::string const Journal::S_KEYWORDS = std::to_string(Journal::KEYWORDS);
std::string const Journal::S_DESCRIPTION = std::to_string(Journal::DESCRIPTION);
std::string const Journal::S_SHOW = std::to_string(Journal::SHOW);
std::string const Journal::S_ITEMS = std::to_string(Journal::ITEMS);
std::string const Journal::S_TAGS = std::to_string(Journal::TAGS);
std::string const Journal::S_SEARCH_TAGS = std::to_string(Journal::SEARCH_TAGS);


int Journal::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(S_NAME)) name.set(obj.getField(S_NAME).String());
  if (obj.hasField(S_SLUG)) slug.set(obj.getField(S_SLUG).String());
  if (obj.hasField(S_KEYWORDS)) keywords.set(obj.getField(S_KEYWORDS).String());
  if (obj.hasField(S_DESCRIPTION))
    description.set(obj.getField(S_DESCRIPTION).String());
  if (obj.hasField(S_SHOW)) {
    int val = obj.getField(S_SHOW).Int();
    show.set(val == 1);
  }
  if (obj.hasField(S_ITEMS)) {
    std::string items_ = obj.getField(S_ITEMS).String();
    shot::split(items_, ',', items);
  }
  if (obj.hasField(S_TAGS)) {
    auto arr = obj.getField(S_TAGS).Array();
    for (auto i: arr) {
      tags.insert(i.String());
    }
  }
  if (obj.hasField(S_SEARCH_TAGS)) {
    auto arr = obj.getField(S_SEARCH_TAGS).Array();
    for (auto i: arr) {
      searchTags.insert(i.String());
    }
  }

  return 0;
}


int Journal::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case NAME:
      name.set(value);
      break;
    case SLUG:
      slug.set(value);
      break;
    case KEYWORDS:
      keywords.set(value);
      break;
    case DESCRIPTION:
      description.set(value);
      break;
    case SHOW:
      show.set(std::stoi(value) == 1);
      break;
    case ITEMS: // skip
      break;
    case TAGS: // skip
      break;
    case SEARCH_TAGS: // skip
      break;
  }

  return 0;
}


void Journal::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (name.has) builder << S_NAME << name.value;
  if (slug.has) builder << S_SLUG << slug.value;
  if (keywords.has) builder << S_KEYWORDS << keywords.value;
  if (description.has) builder << S_DESCRIPTION << description.value;
  if (show.has) {
    builder << S_SHOW << (show.value ? 1 : 0);
  }
  if (not items.empty()) {
    builder << S_ITEMS << shot::join(items, ',');
  }
  if (not tags.empty()) {
    mongo::BSONArrayBuilder bab;
    for (auto& tag: tags) bab.append(tag);
    builder << S_TAGS << bab.arr();
  }
  if (not searchTags.empty()) {
    mongo::BSONArrayBuilder bab;
    for (auto& tag: searchTags) bab.append(tag);
    builder << S_SEARCH_TAGS << bab.arr();
  }
}


void Journal::toCompactFormat(ostream& stream) {
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (name.has) stream << S_NAME << DF << name.value << DF;
  if (slug.has) stream << S_SLUG << DF << slug.value << DF;
  if (keywords.has) stream << S_KEYWORDS << DF << keywords.value << DF;
  if (description.has) stream << S_DESCRIPTION << DF << description.value << DF;
  if (show.has) {
    stream << S_SHOW << DF << (show.value ? '1' : '0') << DF;
  }
  /* if (not items.empty()) { // skip */
  /* } */
  /* if (not tags.empty()) { // skip */
  /* } */
  // skip searchTags
}


Node::~Node() {
}


JournalItems::~JournalItems() {
  for (auto n: nodes) delete n;
}


std::string const Node::S_TYPE = std::to_string(Node::TYPE);
std::string const Node::S_PAGE_ID = std::to_string(Node::PAGE_ID);
std::string const Node::S_STYLE = std::to_string(Node::STYLE);


Block::Block() {
  nodeType = NodeType::Block;
}

Block::~Block() {
}

int Block::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());

  return 0;
}

int Block::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
  }

  return 0;
}

void Block::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
}

void Block::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
}


Header1::Header1() {
  nodeType = NodeType::H1;
}

int Header1::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());

  return 0;
}

int Header1::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
  }

  return 0;
}

void Header1::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
}

void Header1::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
}


std::string const Header2::S_TEXT = std::to_string(Header2::TEXT);


Header2::Header2() {
  nodeType = NodeType::H2;
}

int Header2::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());

  return 0;
}

int Header2::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
  }

  return 0;
}

void Header2::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (text.has) builder << S_TEXT << text.value;
}

void Header2::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
}


std::string const Text::S_TEXT = std::to_string(Text::TEXT);


Text::Text() {
  nodeType = NodeType::Text;
}

int Text::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());

  return 0;
}

int Text::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
  }

  return 0;
}

void Text::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (text.has) builder << S_TEXT << text.value;
}

void Text::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
}


std::string const Code::S_TEXT = std::to_string(Code::TEXT);


Code::Code() {
  nodeType = NodeType::Code;
}

int Code::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());

  return 0;
}

int Code::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
  }

  return 0;
}

void Code::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (text.has) builder << S_TEXT << text.value;
}

void Code::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
}


std::string const Link::S_SRC = std::to_string(Link::SRC);
std::string const Link::S_ALT = std::to_string(Link::ALT);
std::string const Link::S_TEXT = std::to_string(Link::TEXT);


Link::Link() {
  nodeType = NodeType::Link;
}

int Link::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_SRC)) src.set(obj.getField(S_SRC).String());
  if (obj.hasField(S_ALT)) alt.set(obj.getField(S_ALT).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());

  return 0;
}

int Link::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case SRC:
      src.set(value);
      break;
    case ALT:
      alt.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
  }

  return 0;
}

void Link::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (src.has) builder << S_SRC << src.value;
  if (alt.has) builder << S_ALT << alt.value;
  if (text.has) builder << S_TEXT << text.value;
}

void Link::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (src.has) stream << S_SRC << DF << src.value << DF;
  if (alt.has) stream << S_ALT << DF << alt.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
}


std::string const Video::S_TEXT = std::to_string(Video::TEXT);


Video::Video() {
  nodeType = NodeType::Video;
}

int Video::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());

  return 0;
}

int Video::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
  }

  return 0;
}

void Video::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (text.has) builder << S_TEXT << text.value;
}

void Video::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
}


std::string const GoogleMap::S_ZOOM = std::to_string(GoogleMap::ZOOM);
std::string const GoogleMap::S_LAT = std::to_string(GoogleMap::LAT);
std::string const GoogleMap::S_LNG = std::to_string(GoogleMap::LNG);


GoogleMap::GoogleMap() {
  nodeType = NodeType::GoogleMap;
}

int GoogleMap::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_ZOOM)) zoom.set(obj.getField(S_ZOOM).Int());
  if (obj.hasField(S_LAT)) lat.set(obj.getField(S_LAT).Double());
  if (obj.hasField(S_LNG)) lng.set(obj.getField(S_LNG).Double());

  return 0;
}

int GoogleMap::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case ZOOM:
      if (not value.empty()) {
        try {
          zoom.set(std::stoi(value));
        } catch (...) {
        }
      }
      break;
    case LAT:
      if (not value.empty()) {
        try {
          lat.set(std::stof(value));
        } catch (...) {
        }
      }
      break;
    case LNG:
      if (not value.empty()) {
        try {
          lng.set(std::stof(value));
        } catch (...) {
        }
      }
      break;
  }

  return 0;
}

void GoogleMap::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (zoom.has) builder << S_ZOOM << zoom.value;
  if (lat.has) builder << S_LAT << lat.value;
  if (lng.has) builder << S_LNG << lng.value;
}

void GoogleMap::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (zoom.has) stream << S_ZOOM << DF << zoom.value << DF;
  if (lat.has) stream << S_LAT << DF << lat.value << DF;
  if (lng.has) stream << S_LNG << DF << lng.value << DF;
}


std::string const File::S_FILENAME = std::to_string(File::FILENAME);
std::string const File::S_TEXT = std::to_string(File::TEXT);
std::string const File::S_ALT = std::to_string(File::ALT);


File::File() {
  nodeType = NodeType::File;
}

int File::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_FILENAME)) filename.set(obj.getField(S_FILENAME).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());
  if (obj.hasField(S_ALT)) alt.set(obj.getField(S_ALT).String());

  return 0;
}

int File::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case FILENAME:
      filename.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
    case ALT:
      alt.set(value);
      break;
  }

  return 0;
}

void File::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (filename.has) builder << S_FILENAME << filename.value;
  if (text.has) builder << S_TEXT << text.value;
  if (alt.has) builder << S_ALT << alt.value;
}

void File::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (filename.has) stream << S_FILENAME << DF << filename.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
  if (alt.has) stream << S_ALT << DF << alt.value << DF;
}


// for 1080p, 2160p
std::vector<int> const Image::THUMB_SIZES = {300,225, 600,450};
std::vector<int> const Image::SIZES = {1280,720, 1920,1080, 2560,1440,
  3840,2160};
std::string const Image::S_FILENAME = std::to_string(Image::FILENAME);
std::string const Image::S_ALT = std::to_string(Image::ALT);


Image::Image() {
  nodeType = NodeType::Image;
}

int Image::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_FILENAME)) filename.set(obj.getField(S_FILENAME).String());
  if (obj.hasField(S_ALT)) alt.set(obj.getField(S_ALT).String());

  return 0;
}

int Image::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case FILENAME:
      filename.set(value);
      break;
    case ALT:
      alt.set(value);
      break;
  }

  return 0;
}

void Image::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (filename.has) builder << S_FILENAME << filename.value;
  if (alt.has) builder << S_ALT << alt.value;
}

void Image::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (filename.has) stream << S_FILENAME << DF << filename.value << DF;
  if (alt.has) stream << S_ALT << DF << alt.value << DF;
}


// for fullhd (2k) and 4k
std::vector<int> const Gallery::THUMB_SIZES = {300,225, 600,450};
// for fullhd (2k) and 4k
std::vector<int> const Gallery::SIZES = {1280,720, 1920,1080, 2560,1440,
  3840,2160};

std::string const Gallery::S_IMAGES = std::to_string(Gallery::IMAGES);


Gallery::Gallery() {
  nodeType = NodeType::Gallery;
}

int Gallery::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_IMAGES)) {
    std::string imgs = obj.getField(S_IMAGES).String();
    shot::split(imgs, ':', images);
  }

  return 0;
}

int Gallery::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case IMAGES:
      shot::split(const_cast<std::string&>(value), ':', images);
      break;
  }

  return 0;
}

void Gallery::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (images.size() > 0) {
    builder << Gallery::S_IMAGES << shot::join(images, ':');
  }
}

void Gallery::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (images.size() > 0) {
    stream << Gallery::S_IMAGES << DF << shot::join(images, ':') << DF;
  }
}


std::string const BigSlider::S_IMAGES = std::to_string(BigSlider::IMAGES);


BigSlider::BigSlider() {
  nodeType = NodeType::BigSlider;
}

int BigSlider::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_IMAGES)) {
    std::string imgs = obj.getField(S_IMAGES).String();
    shot::split(imgs, ':', images);
  }

  return 0;
}

int BigSlider::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case IMAGES:
      shot::split(const_cast<std::string&>(value), ':', images);
      break;
  }

  return 0;
}

void BigSlider::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (images.size() > 0) {
    builder << BigSlider::S_IMAGES << shot::join(images, ':');
  }
}

void BigSlider::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (images.size() > 0) {
    stream << BigSlider::S_IMAGES << DF << shot::join(images, ':') << DF;
  }
}


std::string const MiniSlider::S_IMAGES = std::to_string(MiniSlider::IMAGES);


MiniSlider::MiniSlider() {
  nodeType = NodeType::MiniSlider;
}

int MiniSlider::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_IMAGES)) {
    std::string imgs = obj.getField(S_IMAGES).String();
    shot::split(imgs, ':', images);
  }

  return 0;
}

int MiniSlider::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case IMAGES:
      shot::split(const_cast<std::string&>(value), ':', images);
      break;
  }

  return 0;
}

void MiniSlider::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (images.size() > 0) {
    builder << MiniSlider::S_IMAGES << shot::join(images, ':');
  }
}

void MiniSlider::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (images.size() > 0) {
    stream << MiniSlider::S_IMAGES << DF << shot::join(images, ':') << DF;
  }
}


std::string const Anchor::S_NAME = std::to_string(Anchor::NAME);


Anchor::Anchor() {
  nodeType = NodeType::Anchor;
}

int Anchor::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_NAME)) name.set(obj.getField(S_NAME).String());

  return 0;
}

int Anchor::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case NAME:
      name.set(value);
      break;
  }

  return 0;
}

void Anchor::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (name.has) builder << S_NAME << name.value;
}

void Anchor::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (name.has) stream << S_NAME << DF << name.value << DF;
}


Break::Break() {
  nodeType = NodeType::Break;
}

int Break::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());

  return 0;
}

int Break::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
  }

  return 0;
}

void Break::toDbFormat(bson::bob& builder) {
  if (id.has) {
    builder << shot::S_ID << mongo::OID(id.value)
      << Node::S_TYPE << static_cast<int>(nodeType);
  }
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
}

void Break::toCompactFormat(ostream& stream) {
  stream << static_cast<int>(nodeType) << DR;
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
}


std::string const PagingSearch::S_QUERY = std::to_string(PagingSearch::QUERY);
std::string const PagingSearch::S_LEFT_ID =
    std::to_string(PagingSearch::LEFT_ID);
std::string const PagingSearch::S_RIGHT_ID =
    std::to_string(PagingSearch::RIGHT_ID);
std::string const PagingSearch::S_PAGE_COUNT =
    std::to_string(PagingSearch::PAGE_COUNT);
std::string const PagingSearch::S_LEFT_EXISTS =
    std::to_string(PagingSearch::LEFT_EXISTS);
std::string const PagingSearch::S_RIGHT_EXISTS =
    std::to_string(PagingSearch::RIGHT_EXISTS);


int PagingSearch::fromDbFormat(bson::bo& obj) {
  // skip implementation - not needed

  return 0;
}

int PagingSearch::parseField(int code, std::string const& value) {
  switch (code) {
    case QUERY:
      query.set(value);
      break;
    case LEFT_ID:
      leftId.set(value);
      break;
    case RIGHT_ID:
      rightId.set(value);
      break;
    // skip fields below
    /* case PAGE_COUNT: */
    /*   pageCount.set(std::stoi(value)); */
    /*   break; */
    /* case LEFT_EXISTS: */
    /*   leftExists.set(std::stoi(value) == 1); */
    /*   break; */
    /* case RIGHT_EXISTS: */
    /*   rightExists.set(std::stoi(value) == 1): */
    /*   break; */
  }

  return 0;
}

void PagingSearch::toDbFormat(bson::bob& builder) {
  // skip
}

void PagingSearch::toCompactFormat(ostream& stream) {
  if (query.has) stream << S_QUERY << DF << query.value << DF;
  if (leftId.has) stream << S_LEFT_ID << DF << leftId.value << DF;
  if (rightId.has) stream << S_RIGHT_ID << DF << rightId.value << DF;
  if (pageCount.has) stream << S_PAGE_COUNT << DF << pageCount.value << DF;
  if (leftExists.has) stream << S_LEFT_EXISTS << DF <<
    (leftExists.value ? '1' : '0') << DF;
  if (rightExists.has) stream << S_RIGHT_EXISTS << DF <<
    (rightExists.value ? '1' : '0') << DF;

}


std::string const FileUpload::S_POLYMORPH =
    std::to_string(FileUpload::POLYMORPH);
std::string const FileUpload::S_COLLECTION =
    std::to_string(FileUpload::COLLECTION);
std::string const FileUpload::S_FIELD = std::to_string(FileUpload::FIELD);
std::string const FileUpload::S_OBJ_ID = std::to_string(FileUpload::OBJ_ID);


int FileUpload::fromDbFormat(bson::bo& obj) {
  // skip implementation - not needed

  return 0;
}


int FileUpload::parseField(int code, std::string const& value) {
  switch (code) {
    case POLYMORPH:
      try {
        polymorph.set(std::stoi(value));
      } catch (...) {
      }
      break;
    case COLLECTION:
      try {
        collection.set(std::stoi(value));
      } catch (...) {
      }
      break;
    case FIELD:
      try {
        field.set(std::stoi(value));
      } catch (...) {
      }
      break;
    case OBJ_ID:
      objId.set(value);
      break;
  }

  return 0;
}


void FileUpload::toDbFormat(bson::bob& builder) {
  // skip
}


void FileUpload::toCompactFormat(ostream& stream) {
  if (polymorph.has) stream << S_POLYMORPH << DF << polymorph.value << DF;
  if (collection.has) stream << S_COLLECTION << DF << collection.value << DF;
  if (field.has) stream << S_FIELD << DF << field.value << DF;
  if (objId.has) stream << S_OBJ_ID << DF << objId.value << DF;
}

  
} /* namespace journal */
