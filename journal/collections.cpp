#include "collections.h"
#include <algorithm>
#include "shot/utils.h"
#include "shot/translit.h"
#include "shot/Options.h"
#include "imgutil/imgutil.h"

namespace journal {
  

ItemsCollection::ItemsCollection(shot::DbClient* db, char const* table) {
  this->db = db;
  this->table = table;
}


void ItemsCollection::genId(Node& node, std::ostream& updates) {
  std::string id = shot::newId();
  node.id.set(id);
  updates << shot::ID << DF << id << DF;
}


NodePtr ItemsCollection::get(string& id) {
  return nullptr;
}


void ItemsCollection::update(string& id, Node& node, ostream& updates) {
}


void ItemsCollection::appendH1(Header1& header, std::ostream& updates) {
  if (header.id.value.length() < shot::OID_SIZE) genId(header, updates);

  bson::bob builder;
  header.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendH1Raw(std::string& obj, ostream& updates) {
  Header1 header;
  header.fromCompactFormat(obj);

  appendH1(header, updates);

  return header.id.value;
}

void ItemsCollection::appendH2(Header2& header, std::ostream& updates) {
  if (header.id.value.length() < shot::OID_SIZE) genId(header, updates);

  bson::bob builder;
  header.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendH2Raw(std::string& obj, ostream& updates) {
  Header2 header;
  header.fromCompactFormat(obj);

  appendH2(header, updates);

  return header.id.value;
}

void ItemsCollection::appendText(Text& text, std::ostream& updates) {
  if (text.id.value.length() < shot::OID_SIZE) genId(text, updates);

  bson::bob builder;
  text.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendTextRaw(std::string& obj, std::ostream& updates) {
  Text text;
  text.fromCompactFormat(obj);

  appendText(text, updates);

  return text.id.value;
}

void ItemsCollection::appendCode(Code& code, std::ostream& updates) {
  if (code.id.value.length() < shot::OID_SIZE) genId(code, updates);

  bson::bob builder;
  code.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendCodeRaw(std::string& obj, std::ostream& updates) {
  Code code;
  code.fromCompactFormat(obj);

  appendCode(code, updates);

  return code.id.value;
}

void ItemsCollection::appendLink(Link& link, std::ostream& updates) {
  if (link.id.value.length() < shot::OID_SIZE) genId(link, updates);

  bson::bob builder;
  link.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendLinkRaw(std::string& obj, std::ostream& updates) {
  Link link;
  link.fromCompactFormat(obj);

  appendLink(link, updates);

  return link.id.value;
}

void ItemsCollection::appendVideo(Video& video, std::ostream& updates) {
  if (video.id.value.length() < shot::OID_SIZE) genId(video, updates);

  bson::bob builder;
  video.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendVideoRaw(std::string& obj, std::ostream& updates) {
  Video video;
  video.fromCompactFormat(obj);

  appendVideo(video, updates);

  return video.id.value;
}

void ItemsCollection::appendGoogleMap(GoogleMap& map, std::ostream& updates) {
  if (map.id.value.length() < shot::OID_SIZE) genId(map, updates);

  bson::bob builder;
  map.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendGoogleMapRaw(std::string& obj, std::ostream& updates) {
  GoogleMap map;
  map.fromCompactFormat(obj);

  // debug
  std::cout << "obj: " << obj << std::endl;
  std::cout << "lng: " << std::to_string(map.lng.value) << std::endl;
  std::cout << "lat: " << std::to_string(map.lat.value) << std::endl;

  appendGoogleMap(map, updates);

  return map.id.value;
}

void ItemsCollection::appendFile(File& file, std::ostream& updates) {
  if (file.id.value.length() < shot::OID_SIZE) genId(file, updates);

  bson::bob builder;
  file.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendFileRaw(std::string& obj, std::ostream& updates) {
  File file;
  file.fromCompactFormat(obj);

  appendFile(file, updates);

  return file.id.value;
}

void ItemsCollection::appendImage(Image& image, std::ostream& updates) {
  if (image.id.value.length() < shot::OID_SIZE) genId(image, updates);

  bson::bob builder;
  image.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendImageRaw(std::string& obj, std::ostream& updates) {
  Image image;
  image.fromCompactFormat(obj);

  appendImage(image, updates);

  return image.id.value;
}

void ItemsCollection::appendGallery(Gallery& gallery, std::ostream& updates) {
  if (gallery.id.value.length() < shot::OID_SIZE) genId(gallery, updates);

  bson::bob builder;
  gallery.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendGalleryRaw(std::string& obj,
    std::ostream& updates) {
  Gallery gallery;
  gallery.fromCompactFormat(obj);

  appendGallery(gallery, updates);

  return gallery.id.value;
}

void ItemsCollection::appendBigSlider(BigSlider& slider,
    std::ostream& updates) {
  if (slider.id.value.length() < shot::OID_SIZE) genId(slider, updates);

  bson::bob builder;
  slider.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendBigSliderRaw(std::string& obj,
    std::ostream& updates) {
  BigSlider slider;
  slider.fromCompactFormat(obj);

  appendBigSlider(slider, updates);

  return slider.id.value;
}

void ItemsCollection::appendMiniSlider(MiniSlider& slider,
    std::ostream& updates) {
  if (slider.id.value.length() < shot::OID_SIZE) genId(slider, updates);

  bson::bob builder;
  slider.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendMiniSliderRaw(std::string& obj,
    std::ostream& updates) {
  MiniSlider slider;
  slider.fromCompactFormat(obj);

  appendMiniSlider(slider, updates);

  return slider.id.value;
}

void ItemsCollection::appendAnchor(Anchor& anchor, std::ostream& updates) {
  if (anchor.id.value.length() < shot::OID_SIZE) genId(anchor, updates);

  bson::bob builder;
  anchor.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendAnchorRaw(std::string& obj,
    std::ostream& updates) {
  Anchor anchor;
  anchor.fromCompactFormat(obj);

  appendAnchor(anchor, updates);

  return anchor.id.value;
}

void ItemsCollection::appendBreak(Break& break_, std::ostream& updates) {
  if (break_.id.value.length() < shot::OID_SIZE) genId(break_, updates);

  bson::bob builder;
  break_.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}

std::string ItemsCollection::appendBreakRaw(std::string& obj,
    std::ostream& updates) {
  Break break_;
  break_.fromCompactFormat(obj);

  appendBreak(break_, updates);

  return break_.id.value;
}

void ItemsCollection::removeH1(std::string& id) {
  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  Header1 header;
  header.fromDbFormat(obj);

  // TODO: remove some stuff - images etc

  remove(id);
}

void ItemsCollection::removeH2(std::string& id) {
  remove(id);
}

void ItemsCollection::removeText(std::string& id) {
  remove(id);
}

void ItemsCollection::removeCode(std::string& id) {
  remove(id);
}

void ItemsCollection::removeLink(std::string& id) {
  remove(id);
}

void ItemsCollection::removeVideo(std::string& id) {
  remove(id);
}


void ItemsCollection::removeGoogleMap(GoogleMap& map) {
  if (!map.icon.has or map.icon.value.empty()) return;

  std::string old = shot::Options::instance().imgDir + map.icon.value;

  if (shot::pathExists(old.data())) {
    shot::rm(old);
  }
}

void ItemsCollection::removeGoogleMap(std::string& id) {
  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  GoogleMap map;
  map.fromDbFormat(obj);

  removeGoogleMap(map);
  remove(id);
}

void ItemsCollection::removeFile(File& file) {
  if (!file.filename.has or file.filename.value.empty()) return;

  std::string old = shot::Options::instance().dataDir + file.filename.value;

  if (shot::pathExists(old.data())) {
    shot::rm(old);
  }
}

void ItemsCollection::removeFile(std::string& id) {
  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  File file;
  file.fromDbFormat(obj);

  removeFile(file);
  remove(id);
}

void ItemsCollection::removeImage(Image& image) {
  if (image.filename.has and !image.filename.value.empty()) {
    std::string original = shot::Options::instance().imgDir +
      image.filename.value;
    if (shot::pathExists(original.data())) {
      shot::rm(original);

      // remove thumbs
      size_t width, height;
      for (size_t i = 0; i < Image::THUMB_SIZES.size(); i+= 2) {
        width = Image::THUMB_SIZES[i];
        height = Image::THUMB_SIZES[i+1];

        std::string thumb = createFilename(shot::Options::instance().imgDir,
            image.filename.value, width, height);

        shot::rm(thumb);
      }
      
      // remove sized images
      for (size_t i = 0; i < Image::SIZES.size(); i += 2) {
        width = Image::SIZES[i];
        height = Image::SIZES[i+1];

        std::string img = createFilename(shot::Options::instance().imgDir,
            image.filename.value, width, height);

        shot::rm(img);
      }
    }
  }
}

void ItemsCollection::removeImage(std::string& id) {
  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  Image image;
  image.fromDbFormat(obj);

  removeImage(image);
  remove(id);
}

void ItemsCollection::removeGallery(Gallery& gallery) {
  for (auto& filename: gallery.images) {
    removeGalleryImage(filename);
  }
}

void ItemsCollection::removeGallery(std::string& id) {
  if (id.length() != shot::OID_SIZE) return;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  Gallery gallery;
  gallery.fromDbFormat(obj);

  removeGallery(gallery);
  remove(id);
}


void ItemsCollection::removeBigSliderImage(std::string& filename,
    std::vector<int>& metrics) {
  std::string original = shot::Options::instance().imgDir + filename;

  shot::rm(original);

  // remove images
  size_t width, height;
  for (size_t i = 0; i < metrics.size(); i += 2) {
    width = metrics[i];
    height = metrics[i+1];

    std::string im = createFilename(shot::Options::instance().imgDir,
        filename, width, height);

    shot::rm(im);

    // remove 2x versions
    width *= 2;
    height *= 2;

    std::string im2 = createFilename(shot::Options::instance().imgDir,
        filename, width, height);

    shot::rm(im2);
  }
}

void ItemsCollection::removeBigSlider(BigSlider& slider) {
  for (auto& filename: slider.images) {
    removeBigSliderImage(filename, slider.size);
  }
}

void ItemsCollection::removeBigSlider(std::string& id) {
  if (id.length() != shot::OID_SIZE) return;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  BigSlider slider;
  slider.fromDbFormat(obj);

  removeBigSlider(slider);
  remove(id);
}

void ItemsCollection::removeMiniSliderImage(std::string& filename,
    std::vector<int>& metrics) {
  std::string original = shot::Options::instance().imgDir + filename;

  shot::rm(original);

  // remove images
  size_t width, height;
  for (size_t i = 0; i < metrics.size(); i += 2) {
    width = metrics[i];
    height = metrics[i+1];

    std::string im = createFilename(shot::Options::instance().imgDir,
        filename, width, height);

    shot::rm(im);

    // remove 2x versions
    width *= 2;
    height *= 2;

    std::string im2 = createFilename(shot::Options::instance().imgDir,
        filename, width, height);

    shot::rm(im2);
  }
}

void ItemsCollection::removeMiniSlider(MiniSlider& slider) {
  for (auto& filename: slider.images) {
    removeMiniSliderImage(filename, slider.size);
  }
}

void ItemsCollection::removeMiniSlider(std::string& id) {
  if (id.length() != shot::OID_SIZE) return;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  MiniSlider slider;
  slider.fromDbFormat(obj);

  removeMiniSlider(slider);
  remove(id);
}

void ItemsCollection::removeAnchor(std::string& id) {
  remove(id);
}

void ItemsCollection::removeBreak(std::string& id) {
  remove(id);
}

void ItemsCollection::updateH1(std::string& id, std::string& params,
    std::ostream& updates) {
  Header1 item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateH2(std::string& id, std::string& params,
    std::ostream& updates) {
  Header2 item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateText(std::string& id, std::string& params,
    std::ostream& updates) {
  Text item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateCode(std::string& id, std::string& params,
    std::ostream& updates) {
  Code item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateLink(std::string& id, std::string& params,
    std::ostream& updates) {
  Link item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateVideo(std::string& id, std::string& params,
    std::ostream& updates) {
  Video item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateGoogleMap(std::string& id, std::string& params,
    std::ostream& updates) {
  GoogleMap item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateFile(std::string& id, std::string& params,
    std::ostream& updates) {
  File item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateImage(std::string& id, std::string& params,
    std::ostream& updates) {
  Image item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateGallery(std::string& id, std::string& params,
    std::ostream& updates) {
  Gallery item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateBigSlider(std::string& id, std::string& params,
    std::ostream& updates) {
  BigSlider item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateMiniSlider(std::string& id, std::string& params,
    std::ostream& updates) {
  MiniSlider item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateAnchor(std::string& id, std::string& params,
    std::ostream& updates) {
  Anchor item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateBreak(std::string& id, std::string& params,
    std::ostream& updates) {
  Break item;
  item.fromCompactFormat(params);

  bson::bob builder;
  item.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}

void ItemsCollection::updateItem(int nodeType, std::string& id,
    std::string& params, std::ostream& updates) {
  switch (static_cast<NodeType>(nodeType)) {
    case NodeType::None:
    case NodeType::Block:
      break;
    case NodeType::H1:
      updateH1(id, params, updates);
      break;
    case NodeType::H2:
      updateH2(id, params, updates);
      break;
    case NodeType::Text:
      updateText(id, params, updates);
      break;
    case NodeType::Code:
      updateCode(id, params, updates);
      break;
    case NodeType::Link:
      updateLink(id, params, updates);
      break;
    case NodeType::Video:
      updateVideo(id, params, updates);
      break;
    case NodeType::GoogleMap:
      updateGoogleMap(id, params, updates);
      break;
    case NodeType::File:
      updateFile(id, params, updates);
      break;
    case NodeType::Image:
      updateImage(id, params, updates);
      break;
    case NodeType::Gallery:
      updateGallery(id, params, updates);
      break;
    case NodeType::BigSlider:
      updateBigSlider(id, params, updates);
      break;
    case NodeType::MiniSlider:
      updateMiniSlider(id, params, updates);
      break;
    case NodeType::Anchor:
      updateAnchor(id, params, updates);
      break;
    case NodeType::Break:
      updateBreak(id, params, updates);
      break;
  }
}


bool ItemsCollection::uploadFiles(FileUpload& fu,
    std::vector<shot::File>& files, std::ostream& updates) {
  switch (static_cast<NodeType>(fu.polymorph.value)) {
    case NodeType::GoogleMap:
      {
        std::string filename = files[0].path;
        uploadGoogleMapIcon(fu.objId.value, filename, updates);
      }
      return true;
    case NodeType::File:
      {
        std::string filename = files[0].path;
        uploadFile(fu.objId.value, filename, updates);
      }
      return true;
    case NodeType::Image:
      {
        std::string filename = files[0].path;
        uploadImage(fu.objId.value, filename, updates);
      }
      return true;
    case NodeType::Gallery:
      {
        std::vector<std::string> filenames;
        for (auto& file: files) {
          filenames.push_back(file.path);
        }
        uploadGalleryImage(fu.objId.value, filenames, updates);
      }
      return true;
    case NodeType::BigSlider:
      {
        std::vector<std::string> filenames;
        for (auto& file: files) {
          filenames.push_back(file.path);
        }
        uploadBigSliderImage(fu.objId.value, filenames, updates);
      }
      return true;
    case NodeType::MiniSlider:
      {
        std::vector<std::string> filenames;
        for (auto& file: files) {
          filenames.push_back(file.path);
        }
        uploadMiniSliderImage(fu.objId.value, filenames, updates);
      }
      return true;
  }

  return false;
}

void ItemsCollection::uploadGoogleMapIcon(std::string& id,
    std::string& filename, std::ostream& updates) {
  if (id.length() != shot::OID_SIZE) return;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  GoogleMap map;
  map.fromDbFormat(obj);

  // remove old file
  removeGoogleMap(map);

  std::string name = shot::getFilename(filename);

  // move file from tmp to data directory
  if (shot::pathExists(filename.data())) {
    std::string dest = shot::Options::instance().imgDir + name;
    /* shot::moveFile(dest, filename); */
    shot::copyFile(dest, filename);
    shot::rm(filename);
  }

  // update item in db
  GoogleMap upd;
  bson::bob builder;

  upd.icon.set(name);
  upd.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );

  updates << name << DF;
}

void ItemsCollection::uploadFile(std::string& id, std::string& filename,
    std::ostream& updates) {
  if (id.length() != shot::OID_SIZE) return;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  File file;
  file.fromDbFormat(obj);

  // remove old file
  removeFile(file);

  std::string name = shot::getFilename(filename);

  // move file from tmp to data directory
  if (shot::pathExists(filename.data())) {
    std::string dest = shot::Options::instance().dataDir + name;
    /* shot::moveFile(dest, filename); */
    shot::copyFile(dest, filename);
    shot::rm(filename);
  }

  // update item in db
  File upd;
  bson::bob builder;

  upd.filename.set(name);
  upd.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );

  updates << name << DF;
}


void ItemsCollection::uploadImage(std::string& id, std::string& filename,
    std::ostream& updates) {
  if (id.length() != shot::OID_SIZE) return;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  Image image;
  image.fromDbFormat(obj);

  // remove old file
  removeImage(image);

  std::string name = shot::getFilename(filename);

  // move file from tmp to img directory
  if (shot::pathExists(filename.data())) {
    std::string original = shot::Options::instance().imgDir + name;
    /* shot::moveFile(original, filename); */
    shot::copyFile(original, filename);
    shot::rm(filename);

    // create thumbs
    size_t width, height;
    for (size_t i = 0; i < Image::THUMB_SIZES.size(); i += 2) {
      width = Image::THUMB_SIZES[i];
      height = Image::THUMB_SIZES[i+1];

      std::string thumb = createFilename(shot::Options::instance().imgDir,
          name, width, height);

      resizeThumb(thumb, original, width, height);
    }

    // create sized images
    for (size_t i = 0; i < Image::SIZES.size(); i += 2) {
      width = Image::SIZES[i];
      height = Image::SIZES[i+1];

      std::string resized = createFilename(shot::Options::instance().imgDir,
          name, width, height);

      resizeImage(resized, original, width, height);
    }
  }

  // update item in db
  File upd;
  bson::bob builder;

  upd.filename.set(name);
  upd.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );

  updates << name << DF;
}


void ItemsCollection::uploadGalleryImage(std::string& id,
    std::vector<std::string>& filenames, std::ostream& updates) {
  if (id.length() != shot::OID_SIZE) return;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  Gallery gallery;
  gallery.fromDbFormat(obj);

  Gallery upd;
  upd.images = gallery.images;

  for (auto& filename: filenames) {
    // move each file from tmp to img directory
    std::string name = shot::getFilename(filename);
    std::string original = shot::Options::instance().imgDir + name;

    shot::copyFile(original, filename);
    shot::rm(filename);

    // create thumbs
    size_t width, height;
    for (size_t i = 0; i < Gallery::THUMB_SIZES.size(); i += 2) {
      width = Gallery::THUMB_SIZES[i];
      height = Gallery::THUMB_SIZES[i+1];

      std::string thumb = createFilename(shot::Options::instance().imgDir,
          name, width, height);

      resizeThumb(thumb, original, width, height);
    }

    // create sized images
    for (size_t i = 0; i < Gallery::SIZES.size(); i += 2) {
      width = Gallery::SIZES[i];
      height = Gallery::SIZES[i+1];

      std::string resized = createFilename(shot::Options::instance().imgDir,
          name, width, height);

      resizeImage(resized, original, width, height);
    }

    upd.images.push_back(name);
    updates << name << DF;
  }

  // update item in db
  bson::bob builder;

  upd.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}


void ItemsCollection::removeGalleryImage(std::string& filename) {
  std::string original = shot::Options::instance().imgDir + filename;
  if (!shot::pathExists(original.data())) return;

  shot::rm(original);

  // remove thumbs
  size_t width, height;
  for (size_t i = 0; i < Gallery::THUMB_SIZES.size(); i += 2) {
    width = Gallery::THUMB_SIZES[i];
    height = Gallery::THUMB_SIZES[i+1];

    std::string thumb = createFilename(shot::Options::instance().imgDir,
        filename, width, height);

    shot::rm(thumb);
  }
  
  // remove sized images
  for (size_t i = 0; i < Gallery::SIZES.size(); i += 2) {
    width = Gallery::SIZES[i];
    height = Gallery::SIZES[i+1];

    std::string img = createFilename(shot::Options::instance().imgDir,
        filename, width, height);

    shot::rm(img);
  }
}


void ItemsCollection::removeGalleryImage(std::string& id,
    std::string& filename) {
  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  Gallery gallery;
  Gallery upd;
  bson::bob builder;

  gallery.fromDbFormat(obj);
  upd.images = gallery.images;
  shot::remove(filename, upd.images);
  upd.toDbFormat(builder);

  // remove file from disk
  removeGalleryImage(filename);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}


void ItemsCollection::moveGalleryImage(std::string& id, std::string& beforeId) {
}


void ItemsCollection::uploadBigSliderImage(std::string& id,
    std::vector<std::string>& filenames, std::ostream& updates) {
  if (id.length() != shot::OID_SIZE) return;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  BigSlider old;
  old.fromDbFormat(obj);

  BigSlider upd;
  upd.images = old.images;

  for (auto& filename: filenames) {
    // move each file from tmp to img directory
    std::string name = shot::getFilename(filename);
    std::string original = shot::Options::instance().imgDir + name;

    shot::copyFile(original, filename);
    shot::rm(filename);

    // create resized images
    size_t width, height;
    for (size_t i = 0; i < old.size.size(); i += 2) {
      width = old.size[i];
      height = old.size[i+1];

      std::string im = createFilename(shot::Options::instance().imgDir,
          name, width, height);


      resizeThumb(im, original, width, height);

      // create 2x versions
      width *= 2;
      height *= 2;

      std::string im2 = createFilename(shot::Options::instance().imgDir,
          name, width, height);

      resizeThumb(im2, original, width, height);

      std::string thumb = createFilename(shot::Options::instance().imgDir,
          name, 300, 225);

      resizeThumb(thumb, original, 300, 225);
    }

    upd.images.push_back(name);
    updates << name << DF;
  }

  // update images in db
  bson::bob builder;

  upd.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}


void ItemsCollection::uploadMiniSliderImage(std::string& id,
    std::vector<std::string>& filenames, std::ostream& updates) {
  if (id.length() != shot::OID_SIZE) return;

  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return;

  MiniSlider old;
  old.fromDbFormat(obj);

  MiniSlider upd;
  upd.images = old.images;

  for (auto& filename: filenames) {
    // move each file from tmp to img directory
    std::string name = shot::getFilename(filename);
    std::string original = shot::Options::instance().imgDir + name;

    shot::copyFile(original, filename);
    shot::rm(filename);

    // create resized images
    size_t width, height;
    for (size_t i = 0; i < old.size.size(); i += 2) {
      width = old.size[i];
      height = old.size[i+1];

      std::string im = createFilename(shot::Options::instance().imgDir,
          name, width, height);

      resizeThumb(im, original, width, height);

      // create 2x versions
      width *= 2;
      height *= 2;

      std::string im2 = createFilename(shot::Options::instance().imgDir,
          name, width, height);

      resizeThumb(im2, original, width, height);
    }

    upd.images.push_back(name);
    updates << name << DF;
  }

  // update item in db
  bson::bob builder;

  upd.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}


void ItemsCollection::append(Node& node, ostream& updates) {
}


void ItemsCollection::remove(string& id) {
  if (id.length() < shot::OID_SIZE) return;

  db->conn.remove(table, BSON(shot::S_ID << mongo::OID(id)));
}


int ItemsCollection::queryPageItems(std::string pageId, ostream& out) {
  if (pageId.size() < shot::OID_SIZE) return 0;

  auto cursor = db->conn.query(table, BSON(Node::S_PAGE_ID
      << mongo::OID(pageId)));
  return itemsCursorToStream(*cursor, out);
}


/* Collection::Collection(shot::DbClient* db, char const* table, */
/*     char const* itemsTable) */
/*     : items(db, itemsTable) { */
/*   this->db = db; */
/*   this->table = table; */
/* } */


/* void Collection::genId(Journal& journal, std::ostream& updates) { */
/*   std::string id = shot::newId(); */
/*   journal.id.set(id); */
/*   updates << shot::ID << DF << id << DF; */
/* } */


/* void Collection::genSlug(Journal& journal, std::ostream& updates) { */
/*   auto slug = shot::slugify(journal.name.value); */
/*   journal.slug.set(slug); */
/*   updates << Journal::S_SLUG << DF << slug << DF; */
/* } */


/* void Collection::genTags(Journal& journal, std::ostream& updates) { */
/*   shot::createTags(journal.name.value, journal.tags); */
/*   shot::createSearchTags(journal.tags, journal.searchTags); */
/* } */


/* JournalPtr Collection::get(string& id) { */
/*   if (id.length() < shot::OID_SIZE) return nullptr; */

/*   bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id))); */
/*   if (obj.isEmpty()) return nullptr; */

/*   JournalPtr journal(new Journal()); */
/*   journal->fromDbFormat(obj); */

/*   return journal; */
/* } */


/* JournalPtr Collection::getBySlug(string& slug) { */
/*   bson::bo obj = db->conn.findOne(table, BSON(Journal::S_SLUG << slug)); */
/*   if (obj.isEmpty()) return nullptr; */

/*   JournalPtr journal(new Journal()); */
/*   journal->fromDbFormat(obj); */

/*   return journal; */
/* } */


/* void Collection::update(string& id, Journal& journal, ostream& updates) { */
/*   if (journal.name.has) { */
/*     genSlug(journal, updates); */
/*     genTags(journal, updates); */
/*   } */

/*   bson::bob builder; */

/*   journal.toDbFormat(builder); */
/*   db->conn.update(table, */
/*     BSON(shot::S_ID << mongo::OID(id)), */
/*     BSON("$set" << builder.obj()) */
/*   ); */
/* } */

/* void Collection::updateRaw(string& id, string& journal_, ostream& updates) { */
/*   Journal journal; */

/*   int error = journal.fromCompactFormat(journal_); */
/*   if (error != 0) return; */

/*   update(id, journal, updates); */
/* } */


/* void Collection::append(Journal& journal, ostream& updates) { */
/*   if (journal.id.value.length() < shot::OID_SIZE) genId(journal, updates); */
/*   genSlug(journal, updates); */
/*   genTags(journal, updates); */

/*   bson::bob builder; */

/*   journal.toDbFormat(builder); */
/*   db->conn.insert(table, builder.obj()); */
/* } */


/* void Collection::appendRaw(string& journal_, ostream& updates) { */
/*   Journal journal; */

/*   int error = journal.fromCompactFormat(journal_); */
/*   if (error != 0) return; */

/*   append(journal, updates); */
/* } */


/* void Collection::remove(string& id) { */
/*   if (id.length() < shot::OID_SIZE) return; */

/*   db->conn.remove(table, BSON(shot::S_ID << mongo::OID(id))); */
/* } */


/* int Collection::query(int page, std::ostream& out) { */
/*   // TODO: push paging here in query */

/*   auto cursor = db->conn.query(table, */
/*     mongo::Query().sort(shot::S_ID, -1), */
/*     COUNT_PER_PAGE); */
/*   return shot::cursorToStream<Journal>(*cursor, out); */
/* } */


/* /1* void Collection: *1/ */

/* // reset */

/* void Collection::insertField(std::string obj, */
/*     std::string& parentId, int parentField, int nodeType, */
/*     std::ostream& updates) { */
/*   auto journal = get(parentId); */
/*   if (journal.get() == nullptr) return; */

/*   Journal update; */

/*   switch (parentField) { */
/*     case Journal::ITEMS: */
/*       // insert id to journal items field */
/*       break; */
/*   } */
/* } */

/* void Collection::insertBeforeField(std::string obj, std::string beforeId, */
/*     std::string& parentId, int parentField, int nodeType, */
/*     std::ostream& updates) { */
/*   auto journal = get(parentId); */
/*   if (journal.get() == nullptr) return; */

/*   Journal update; */

/*   switch (parentField) { */
/*     case Journal::ITEMS: */
/*       // insertBefore id to journal items field */
/*       break; */
/*   } */
/* } */

/* void Collection::appendField(std::string& obj, */
/*     std::string& parentId, int parentField, int nodeType, */
/*     std::ostream& updates) { */
/*   auto journal = get(parentId); */
/*   if (journal.get() == nullptr) return; */

/*   std::string objId; */

/*   switch (static_cast<NodeType>(nodeType)) { */
/*     case NodeType::Block: */
/*       break; */
/*     case NodeType::H1: */
/*       { */
/*         Header1 header; */
/*         header.fromCompactFormat(obj); */
/*         objId = header.id.value; */

/*         // debug */
/*         std::cout << "objId: " << objId << std::endl; */

/*         items.appendH1(header, updates); */

/*         // debug */
/*         std::cout << "header.id: " << header.id.value << std::endl; */
/*       } */
/*       break; */
/*     case NodeType::H2: */
/*       { */
/*         /1* Header2 header; *1/ */
/*         /1* header.fromCompactFormat(obj); *1/ */
/*         /1* objId = header.id.value; *1/ */
/*         /1* items.appendH2(header, updates); *1/ */
/*       } */
/*       break; */
/*     case NodeType::Text: */
/*       break; */
/*     case NodeType::Code: */
/*       break; */
/*     case NodeType::Link: */
/*       break; */
/*     case NodeType::Video: */
/*       break; */
/*     case NodeType::GoogleMap: */
/*       break; */
/*     case NodeType::File: */
/*       break; */
/*     case NodeType::Image: */
/*       break; */
/*     case NodeType::Gallery: */
/*       break; */
/*     case NodeType::BigSlider: */
/*       break; */
/*     case NodeType::MiniSlider: */
/*       break; */
/*     case NodeType::Anchor: */
/*       break; */
/*     case NodeType::Break: */
/*       break; */
/*   } */

/*   if (not objId.empty()) { */
/*     Journal upd; */
/*     shot::insert(objId, "", upd.items); */

/*     update(objId, upd, updates); */
/*   } */
/*   /1* switch (parentField) { *1/ */
/*   /1*   case Journal::ITEMS: *1/ */
/*   /1*     // append id to journal items field *1/ */
/*   /1*     break; *1/ */
/*   /1* } *1/ */
/* } */

/* void Collection::moveField(std::string& id, std::string& beforeId, */
/*     std::string& parentId, int parentField, int nodeType) { */
/*   auto journal = get(parentId); */
/*   if (journal.get() == nullptr) return; */

/*   Journal update; */

/*   switch (parentField) { */
/*     case Journal::ITEMS: */
/*       // move id */
/*       break; */
/*   } */
/* } */

/* void Collection::removeField(std::string& id, std::string& parentId, */
/*     int parentField, int nodeType) { */
/*   // get journal */
/*   auto journal = get(parentId); */
/*   if (journal.get() == nullptr) return; // parent not found */
  

/*   switch (parentField) { */
/*     case Journal::ITEMS: */
/*       // remove id from journal items field */
      
/*       items.remove(id); */
/*       break; */
/*   } */
/* } */

/* void Collection::updateField(std::string& id, std::string& params, int parentField, */
/*     int nodeType, std::ostream& updates) { */
/*   std::cout << "Collection.updateField not implemented\n"; */
/* } */


void Collection::genId(Journal& journal, std::ostream& updates) {
  std::string id = shot::newId();
  journal.id.set(id);
  updates << shot::ID << DF << id << DF;
}


void Collection::genSlug(Journal& journal, std::ostream& updates) {
  auto slug = shot::slugify(journal.name.value);
  journal.slug.set(slug);
  updates << Journal::S_SLUG << DF << slug << DF;
}


void Collection::genKeywords(Journal& journal, std::ostream& updates) {
  auto keywords = shot::joinSet(journal.tags, ',');
  journal.keywords.set(keywords);
  updates << Journal::S_KEYWORDS << DF << keywords << DF;
}


void Collection::genTags(Journal& journal, std::ostream& updates) {
  shot::createTags(journal.name.value, journal.tags);
  shot::createSearchTags(journal.tags, journal.searchTags);

  if (not journal.tags.empty()) genKeywords(journal, updates);
}

Collection::Collection(shot::DbClient* db,
    char const* table, int tableCode,
    char const* itemsTable)
    : items(db, itemsTable) {
  this->db = db;
  this->table = table;
  this->tableCode = tableCode;
}


void Collection::init() {
  // get document
  bson::bo obj = db->conn.findOne(table, bson::bo());
  if (!obj.isEmpty()) return; // document exists - do nothing

  std::string id = shot::newId();
  Journal journal;
  journal.id.set(id);

  bson::bob builder;
  journal.toDbFormat(builder);

  db->conn.insert(table, builder.obj());
}


void Collection::getFirst(Journal& journal) {
  bson::bo obj = db->conn.findOne(table, bson::bo());

  journal.fromDbFormat(obj);
}


JournalPtr Collection::get(std::string& id) {
  bson::bo obj = db->conn.findOne(table, BSON(shot::S_ID << mongo::OID(id)));
  if (obj.isEmpty()) return nullptr;

  JournalPtr doc(new Journal());
  doc->fromDbFormat(obj);

  return doc;
}


JournalPtr Collection::getBySlug(string& slug) {
  bson::bo obj = db->conn.findOne(table, BSON(Journal::S_SLUG << slug));
  if (obj.isEmpty()) return nullptr;

  JournalPtr journal(new Journal());
  journal->fromDbFormat(obj);

  return journal;
}


void Collection::update(std::string& id, Journal& doc, ostream& updates) {
  if (doc.name.has) {
    Collection::genSlug(doc, updates);
    Collection::genTags(doc, updates);
  }

  bson::bob builder;

  doc.toDbFormat(builder);

  db->conn.update(table,
    BSON(shot::S_ID << mongo::OID(id)),
    BSON("$set" << builder.obj())
  );
}


void Collection::updateRaw(std::string& id, string& params, ostream& updates) {
  Journal journal;
  journal.fromCompactFormat(params);

  update(id, journal, updates);
}


void Collection::append(Journal& journal, ostream& updates) {
  if (journal.id.value.length() < shot::OID_SIZE) genId(journal, updates);
  genSlug(journal, updates);
  genTags(journal, updates);

  bson::bob builder;

  journal.toDbFormat(builder);
  db->conn.insert(table, builder.obj());
}


void Collection::appendRaw(string& journal_, ostream& updates) {
  Journal journal;

  int error = journal.fromCompactFormat(journal_);
  if (error != 0) return;

  append(journal, updates);
}


void Collection::remove(string& id) {
  if (id.length() < shot::OID_SIZE) return;

  // TODO: remove page items

  db->conn.remove(table, BSON(shot::S_ID << mongo::OID(id)));
}


void Collection::insertField(std::string& obj, std::string& beforeId,
    std::string& parentId, int parentField, int nodeType,
    std::ostream& updates) {
  std::string objId;

  auto journal = get(parentId);
  if (journal.get() == nullptr) return;

  switch (static_cast<NodeType>(nodeType)) {
    case NodeType::None:
    case NodeType::Block:
      break;
    case NodeType::H1:
      objId = items.appendH1Raw(obj, updates);
      break;
    case NodeType::H2:
      objId = items.appendH2Raw(obj, updates);
      break;
    case NodeType::Text:
      objId = items.appendTextRaw(obj, updates);
      break;
    case NodeType::Code:
      objId = items.appendCodeRaw(obj, updates);
      break;
    case NodeType::Link:
      objId = items.appendLinkRaw(obj, updates);
      break;
    case NodeType::Video:
      objId = items.appendVideoRaw(obj, updates);
      break;
    case NodeType::GoogleMap:
      objId = items.appendGoogleMapRaw(obj, updates);
      break;
    case NodeType::File:
      objId = items.appendFileRaw(obj, updates);
      break;
    case NodeType::Image:
      objId = items.appendImageRaw(obj, updates);
      break;
    case NodeType::Gallery:
      objId = items.appendGalleryRaw(obj, updates);
      break;
    case NodeType::BigSlider:
      objId = items.appendBigSliderRaw(obj, updates);
      break;
    case NodeType::MiniSlider:
      objId = items.appendMiniSliderRaw(obj, updates);
      break;
    case NodeType::Anchor:
      objId = items.appendAnchorRaw(obj, updates);
      break;
    case NodeType::Break:
      objId = items.appendBreakRaw(obj, updates);
      break;
  }

  if (not objId.empty()) {
    switch (parentField) {
      case Journal::ITEMS:
        Journal upd;
        upd.items = journal->items;

        shot::insert(objId, beforeId, upd.items);
        update(parentId, upd, updates);
        break;

    }
  }
}

void Collection::moveField(std::string& id, std::string& beforeId,
    std::string& parentId, int parentField) {
  auto doc = get(parentId);
  if (doc.get() == nullptr) return;

  switch (parentField) {
    case Journal::ITEMS:
      {
        std::ostringstream dummy;
        Journal upd;
        upd.items = doc->items;

        shot::move(id, beforeId, upd.items);
        update(parentId, upd, dummy);
      }
      break;
  }
}

void Collection::removeField(std::string& id, std::string& parentId,
    int parentField, int nodeType) {
  if (parentId.empty()) return;

  auto doc = get(parentId);
  if (doc.get() == nullptr) return;

  switch (parentField) {
    case Journal::ITEMS:
      {
        removeItem(id, nodeType);

        std::ostringstream dummy;
        Journal upd;
        upd.items = doc->items;

        shot::remove(id, upd.items);
        update(parentId, upd, dummy);
      }
      break;
  }
}

void Collection::removeItem(std::string& id, int nodeType) {
  switch (static_cast<NodeType>(nodeType)) {
    case NodeType::None:
      break;
    case NodeType::Block:
      break;
    case NodeType::H1:
      items.removeH1(id);
      break;
    case NodeType::H2:
      items.removeH2(id);
      break;
    case NodeType::Text:
      items.removeText(id);
      break;
    case NodeType::Code:
      items.removeCode(id);
      break;
    case NodeType::Link:
      items.removeLink(id);
      break;
    case NodeType::Video:
      items.removeVideo(id);
      break;
    case NodeType::GoogleMap:
      items.removeGoogleMap(id);
      break;
    case NodeType::File:
      items.removeFile(id);
      break;
    case NodeType::Image:
      items.removeImage(id);
      break;
    case NodeType::Gallery:
      items.removeGallery(id);
      break;
    case NodeType::BigSlider:
      items.removeBigSlider(id);
      break;
    case NodeType::MiniSlider:
      items.removeMiniSlider(id);
      break;
    case NodeType::Anchor:
      items.removeAnchor(id);
      break;
    case NodeType::Break:
      items.removeBreak(id);
      break;
  }
}

void Collection::updateField(std::string& id, std::string& params,
    int parentField, int nodeType, std::ostream& updates) {
  switch (parentField) {
    case Journal::ITEMS:
      items.updateItem(nodeType, id, params, updates);
      break;
  }
}


int Collection::query(PagingSearch& search, std::ostream& out) {
  bson::bob builder;
  PagingSearch result;
  std::unordered_set<std::string> queryTags;
  mongo::BSONArray arrTags;

  int order = -1; // for right and normal order
  
  if (search.leftId.has and search.leftId.value.size() == shot::OID_SIZE) {
    order = 1;
    builder << shot::S_ID << BSON("$gt" << mongo::OID(search.leftId.value));
  }

  if (search.rightId.has and search.rightId.value.size() == shot::OID_SIZE) {
    builder << shot::S_ID << BSON("$lt" << mongo::OID(search.rightId.value));
  }

  if (search.query.has) { // add tags to query
    shot::createTags(search.query.value, queryTags);

    mongo::BSONArrayBuilder bab;
    for (auto& tag: queryTags) {
      bab.append(BSON(Journal::S_SEARCH_TAGS << tag));
    }
    arrTags = bab.arr();

    builder << "$and" << arrTags;//bab.arr();
  } else { // without query add pageCount
    auto count = db->conn.count(table);
    result.pageCount.set(count);
  }

  auto cursor = db->conn.query(table,
      mongo::Query(builder.obj()).sort(shot::S_ID, order),
      COUNT_PER_PAGE);
  std::vector<Journal> journals;
  shot::cursorToVector<Journal>(*cursor, journals);

  if (search.leftId.has) { // reverse for left order
    std::reverse(journals.begin(), journals.end());
  }

  if (not journals.empty()) { // query left and right exists
    bson::bob lbuilder;
    bson::bob rbuilder;

    auto lid = journals.front().id.value;
    auto rid = journals.back().id.value;

    if (not queryTags.empty()) {
      /* mongo::BSONArrayBuilder bab; */
      /* for (auto& tag: queryTags) { */
      /*   bab.append(BSON(Journal::S_SEARCH_TAGS << tag)); */
      /* } */

      /* auto arr = bab.arr(); */

      lbuilder << "$and" << arrTags;
      rbuilder << "$and" << arrTags;
    }

    lbuilder << shot::S_ID << BSON("$gt" << mongo::OID(lid));
    rbuilder << shot::S_ID << BSON("$lt" << mongo::OID(rid));

    auto lcursor = db->conn.query(table,
        mongo::Query(lbuilder.obj()).sort(shot::S_ID, 1),
        1);
    auto rcursor = db->conn.query(table,
        mongo::Query(rbuilder.obj()).sort(shot::S_ID, -1),
        1);

    result.leftExists.set(lcursor->more());
    if (lcursor->more()) {
      auto lobj = lcursor->next();
      Journal ldoc;
      ldoc.fromDbFormat(lobj);
    }

    result.rightExists.set(rcursor->more());
    if (rcursor->more()) {
      auto robj = rcursor->next();
      Journal rdoc;
      rdoc.fromDbFormat(robj);
    }
  }

  result.toCompactFormat(out);
  out << shot::DELIM_ROW;
  shot::vectorToStream<Journal>(tableCode, journals, out);

  /* return shot::cursorToStream<Journal>(*cursor, out); */
  return journals.size();
}


int itemsCursorToStream(mongo::DBClientCursor& cursor, std::ostream& stream) {
  int counter = 0;

  while (cursor.more()) {
    ++counter;
    bson::bo obj = cursor.next();

    if (not obj.hasField(Node::S_TYPE)) continue;

    int nodeType = obj.getField(Node::S_TYPE).Int();
    std::unique_ptr<Node> node(createNode(static_cast<NodeType>(nodeType)));
    if (node.get() == nullptr) continue;

    node->fromDbFormat(obj);
    node->toCompactFormat(stream);

    stream << shot::DELIM_ROW;
  }

  return counter;
}


Node* createNode(NodeType nodeType) {
  switch (nodeType) {
    case NodeType::None:
    case NodeType::Block:
      break;
    case NodeType::H1:
      return new Header1();
    case NodeType::H2:
      return new Header2();
    case NodeType::Text:
      return new Text();
    case NodeType::Code:
      return new Code();
    case NodeType::Link:
      return new Link();
    case NodeType::Video:
      return new Video();
    case NodeType::GoogleMap:
      return new GoogleMap();
    case NodeType::File:
      return new File();
    case NodeType::Image:
      return new Image();
    case NodeType::Gallery:
      return new Gallery();
    case NodeType::BigSlider:
      return new BigSlider();
    case NodeType::MiniSlider:
      return new MiniSlider();
    case NodeType::Anchor:
      return new Anchor();
    case NodeType::Break:
      return new Break();
  }

  return nullptr;
}


} /* namespace journal */
