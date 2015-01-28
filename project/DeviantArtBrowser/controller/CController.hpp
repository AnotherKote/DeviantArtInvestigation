#ifndef CCONTROLLER_HPP
#define CCONTROLLER_HPP
#include "CRequester.hpp"
#include "CDeviantArtParser.hpp"
#include "CView.hpp"
#include <QMutex>

class CView;
class CController: public QObject
{
   Q_OBJECT
   QMutex mMutex;
   CDeviantArtParser *mDeviantArtParser;
   CRequester mRequester;
   CRequester mRequester1;
   size_t mNumberOfImagesOnPage;
   size_t mOffset;

   CView *mView;
   void loadImages();
   NWindowsGarbage::CRITICAL_SECTION mCriticalSection;
public:
   CController();
   ~CController();
   void loadFullSizePicture(std::shared_ptr<CViewImage> picture);
   void saveFullSizePicture(size_t id);
   void setNumberOfImagesOnPage(size_t number);
   void setOffset();
public slots:
   void loadNextPageSlot();
   void openSourcePageSlot(QString URL);

signals:
   void loadNextPageSignal();
   void openSourcePageSignal(QString URL);
};

#endif // CCONTROLLER_HPP
//#include "main.moc"
