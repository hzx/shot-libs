#include "models.h"


namespace journal {


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
