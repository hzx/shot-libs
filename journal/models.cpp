#include "models.h"


namespace journal {


std::string const Journal::S_NAME = std::to_string(Journal::NAME);
std::string const Journal::S_SLUG = std::to_string(Journal::SLUG);
std::string const Journal::S_KEYWORDS = std::to_string(Journal::KEYWORDS);
std::string const Journal::S_DESCRIPTION = std::to_string(Journal::DESCRIPTION);
std::string const Journal::S_SHOW = std::to_string(Journal::SHOW);
std::string const Journal::S_ITEMS = std::to_string(Journal::ITEMS);
std::string const Journal::S_TAGS = std::to_string(Journal::TAGS);


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
    // TODO: fill items
  }
  if (obj.hasField(S_TAGS)) {
    // TODO: split obj.tags and fill tags
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
    case ITEMS: // TODO: set
      break;
    case TAGS: // TODO: set
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
    // TODO: set
    // builder << S_ITEMS <<
  }
  if (not tags.empty()) {
    // TODO: set
    // builder << S_TAGS <<
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
  if (not items.empty()) {
    // TODO: set
  }
  if (not tags.empty()) {
    // TODO: set
  }
}


JournalItems::~JournalItems() {
  for (auto n: nodes) delete n;
}


Block::Block() {
  code = NodeType::Block;
}


Block::~Block() {
}


Code::Code() {
  code = NodeType::Code;
}


Text::Text() {
  code = NodeType::Text;
}


Header1::Header1() {
  code = NodeType::H1;
}


Header2::Header2() {
  code = NodeType::H2;
}


Link::Link() {
  code = NodeType::Link;
}


Video::Video() {
  code = NodeType::Video;
}


GoogleMap::GoogleMap() {
  code = NodeType::GoogleMap;
}


File::File() {
  code = NodeType::File;
}


Image::Image() {
  code = NodeType::Image;
}


Gallery::Gallery() {
  code = NodeType::Gallery;
}


BigSlider::BigSlider() {
  code = NodeType::BigSlider;
}


MiniSlider::MiniSlider() {
  code = NodeType::MiniSlider;
}


Anchor::Anchor() {
  code = NodeType::Anchor;
}


Break::Break() {
  code = NodeType::Break;
}

  
} /* namespace journal */
