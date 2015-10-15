#ifndef JOURNAL_COLLS_H
#define JOURNAL_COLLS_H

#include "models.h"
#include "shot/DbClient.h"

namespace journal {


class ItemsCollection {
public:
  ItemsCollection(shot::DbClient* db, char const* table);
  void genId(Node& node, std::ostream& updates);
  NodePtr get(string& id);
  /* void updateH1(string& id, Header1& header, ostream& updates); */
  /* void updateH2(string& id, Header2& header, ostream& updates); */
  void update(string& id, Node& node, ostream& updates);

  void appendH1(Header1& header, std::ostream& updates);
  std::string appendH1Raw(std::string& obj, ostream& updates);

  void appendH2(Header2& header, std::ostream& updates);
  std::string appendH2Raw(std::string& obj, std::ostream& updates);

  void appendText(Text& text, std::ostream& updates);
  std::string appendTextRaw(std::string& obj, std::ostream& updates);

  void appendCode(Code& code, std::ostream& updates);
  std::string appendCodeRaw(std::string& obj, std::ostream& updates);

  void appendLink(Link& link, std::ostream& updates);
  std::string appendLinkRaw(std::string& obj, std::ostream& updates);

  void appendVideo(Video& video, std::ostream& updates);
  std::string appendVideoRaw(std::string& obj, std::ostream& updates);

  void appendGoogleMap(GoogleMap& map, std::ostream& updates);
  std::string appendGoogleMapRaw(std::string& obj, std::ostream& updates);

  void appendFile(File& file, std::ostream& updates);
  std::string appendFileRaw(std::string& obj, std::ostream& updates);

  void appendImage(Image& image, std::ostream& updates);
  std::string appendImageRaw(std::string& obj, std::ostream& updates);

  void appendGallery(Gallery& gallery, std::ostream& updates);
  std::string appendGalleryRaw(std::string& obj, std::ostream& updates);

  void appendBigSlider(BigSlider& slider, std::ostream& updates);
  std::string appendBigSliderRaw(std::string& obj, std::ostream& updates);

  void appendMiniSlider(MiniSlider& slider, std::ostream& updates);
  std::string appendMiniSliderRaw(std::string& obj, std::ostream& updates);

  void appendAnchor(Anchor& anchor, std::ostream& updates);
  std::string appendAnchorRaw(std::string& obj, std::ostream& updates);

  void appendBreak(Break& break_, std::ostream& updates);
  std::string appendBreakRaw(std::string& obj, std::ostream& updates);

  void removeH1(std::string& id);
  void removeH2(std::string& id);
  void removeText(std::string& id);
  void removeCode(std::string& id);
  void removeLink(std::string& id);
  void removeVideo(std::string& id);
  void removeGoogleMap(std::string& id);
  void removeFile(std::string& id);
  void removeImage(std::string& id);
  void removeGallery(std::string& id);
  void removeBigSlider(std::string& id);
  void removeMiniSlider(std::string& id);
  void removeAnchor(std::string& id);
  void removeBreak(std::string& id);

  void updateH1(std::string& id, std::string& params, std::ostream& updates);
  void updateH2(std::string& id, std::string& params, std::ostream& updates);
  void updateText(std::string& id, std::string& params, std::ostream& updates);
  void updateCode(std::string& id, std::string& params, std::ostream& updates);
  void updateLink(std::string& id, std::string& params, std::ostream& updates);
  void updateVideo(std::string& id, std::string& params, std::ostream& updates);
  void updateGoogleMap(std::string& id, std::string& params,
      std::ostream& updates);
  void updateFile(std::string& id, std::string& params, std::ostream& updates);
  void updateImage(std::string& id, std::string& params,
      std::ostream& updates);
  void updateGallery(std::string& id, std::string& params,
      std::ostream& updates);
  void updateBigSlider(std::string& id, std::string& params,
      std::ostream& updates);
  void updateMiniSlider(std::string& id, std::string& params,
      std::ostream& updates);
  void updateAnchor(std::string& id, std::string& params,
      std::ostream& updates);
  void updateBreak(std::string& id, std::string& params, std::ostream& updates);

  void updateItem(int nodeType, std::string& id, std::string& params,
      std::ostream& updates);

  void append(Node& node, ostream& updates);
  void remove(string& id);
  int queryPageItems(std::string pageId, ostream& out);

  shot::DbClient* db;
  char const* table;
};


/* class Collection { */
/* public: */
/*   static int const COUNT_PER_PAGE = 16; */

/*   Collection(shot::DbClient* db, char const* table, char const* itemsTable); */
/*   static void genId(Journal& journal, std::ostream& updates); */
/*   static void genSlug(Journal& journal, std::ostream& updates); */
/*   static void genTags(Journal& journal, std::ostream& updates); */
/*   JournalPtr get(string& id); */
/*   JournalPtr getBySlug(string& slug); */
/*   void update(string& id, Journal& journal, ostream& updates); */
/*   void updateRaw(string& id, string& journal, ostream& updates); */
/*   void append(Journal& journal, ostream& updates); */
/*   void appendRaw(string& journal, ostream& updates); */
/*   void remove(string& id); */
/*   int query(int page, std::ostream& out); */

/*   void updateField(std::string& id, std::string params, */
/*       std::string& parentId, std::string& parentField, std::ostream& updates); */

/*   // reset */
  
/*   void insertField(std::string obj, */
/*       std::string& parentId, int parentField, int nodeType, */
/*       std::ostream& updates); */

/*   void insertBeforeField(std::string obj, std::string beforeId, */
/*       std::string& parentId, int parentField, int nodeType, */
/*       std::ostream& updates); */

/*   void appendField(std::string& obj, */
/*       std::string& parentId, int parentField, int nodeType, */
/*       std::ostream& updates); */

/*   void moveField(std::string& id, std::string& beforeId, */
/*       std::string& parentId, int parentField, int nodeType); */

/*   void removeField(std::string& id, std::string& parentId, int parentField, */
/*       int nodeType); */

/*   void updateField(std::string& id, std::string& params, int parentField, */
/*       int nodeType, std::ostream& updates); */

/*   shot::DbClient* db; */
/*   char const* table; */
/*   ItemsCollection items; */
/* }; */


class Collection {
public:
  static int const COUNT_PER_PAGE = 16;
  static void genId(Journal& journal, std::ostream& updates);
  static void genSlug(Journal& journal, std::ostream& updates);
  static void genTags(Journal& journal, std::ostream& updates);

  Collection(shot::DbClient* db, char const* table, char const* itemsTable);
  void init();
  void getFirst(Journal& journal);
  JournalPtr get(std::string& id);
  JournalPtr getBySlug(string& slug);
  void update(std::string& id, Journal& journal, ostream& updates);
  void updateRaw(std::string& id, string& params, ostream& updates);
  void append(Journal& journal, ostream& updates);
  void appendRaw(string& journal, ostream& updates);
  void remove(string& id);

  void insertField(std::string& obj, std::string& beforeId,
      std::string& parentId, int parentField, int nodeType,
      std::ostream& updates);

  void moveField(std::string& id, std::string& beforeId,
      std::string& parentId, int parentField);

  void removeField(std::string& id, std::string& parentId, int parentField,
      int nodeType);

  void removeItem(std::string& id, int nodeType);

  void updateField(std::string& id, std::string& params, int parentField,
      int nodeType, std::ostream& updates);

  int query(int page, std::ostream& out);

  shot::DbClient* db;
  char const* table;
  ItemsCollection items;
};


int itemsCursorToStream(mongo::DBClientCursor& cursor, std::ostream& stream);
Node* createNode(NodeType nodeType);


} /* namespace journal */


#endif /* end of include guard: JOURNAL_COLLS_H */
