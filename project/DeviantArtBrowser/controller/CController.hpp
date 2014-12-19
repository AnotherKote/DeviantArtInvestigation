#ifndef CCONTROLLER_HPP
#define CCONTROLLER_HPP
#include "CRequester.hpp"
#include "CDeviantArtParser.hpp"
#include "model/CModel.hpp"
#include "CView.hpp"

class CView;

class CController
{
   Q_OBJECT

   CDeviantArtParser mDeviantArtParser;
   CRequester mRequester;
   size_t mNumberOfImagesOnPage;
   size_t mOffset;
   CModel * mModel;
   CView *mView;

public:
   CController();

   void loadFullSizePicture(size_t id);
   void saveFullSizePicture(size_t id);
   void setNumberOfImagesOnPage(size_t number);
   void setOffset();
   void loadNextPage();
};

#endif // CCONTROLLER_HPP
