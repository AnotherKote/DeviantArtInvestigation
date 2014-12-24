#ifndef CCONTROLLER_HPP
#define CCONTROLLER_HPP
//#include <QObject>
#include "CRequester.hpp"
#include "CDeviantArtParser.hpp"
#include "CView.hpp"

class CView;
class CController: public QObject
{
   Q_OBJECT

   CDeviantArtParser *mDeviantArtParser;
   CRequester mRequester;
   size_t mNumberOfImagesOnPage;
   size_t mOffset;

   CView *mView;
   void loadImages();

public:
   CController();
   ~CController();
   void loadFullSizePicture(size_t id);
   void saveFullSizePicture(size_t id);
   void setNumberOfImagesOnPage(size_t number);
   void setOffset();

public slots:
   void loadNextPageSlot();

signals:
   void loadNextPageSignal();
};

#endif // CCONTROLLER_HPP
//#include "main.moc"
