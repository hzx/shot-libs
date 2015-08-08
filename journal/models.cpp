#include "models.h"


namespace journal {


JournalItems::~JournalItems() {
  for (auto n: nodes) delete n;
}


Block::Block() {
  code = NT_BLOCK;
}


Block::~Block() {
}


Code::Code() {
  code = NT_CODE;
}


Text::Text() {
  code = NT_TEXT;
}


Header1::Header1() {
  code = NT_H1;
}


Header2::Header2() {
  code = NT_H2;
}


Link::Link() {
  code = NT_LINK;
}


Video::Video() {
  code = NT_VIDEO;
}


GoogleMap::GoogleMap() {
  code = NT_GOOGLE_MAP;
}


File::File() {
  code = NT_FILE;
}


Image::Image() {
  code = NT_IMAGE;
}


Gallery::Gallery() {
  code = NT_GALLERY;
}


BigSlider::BigSlider() {
  code = NT_BIG_SLIDER;
}


MiniSlider::MiniSlider() {
  code = NT_MINI_SLIDER;
}

  
} /* namespace journal */
