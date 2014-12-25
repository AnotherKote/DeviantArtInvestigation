#include "CController.hpp"

CController::CController()
   : mDeviantArtParser(new CDeviantArtParser),
     mNumberOfImagesOnPage(16), ///<@todo remove magic numbers
     mOffset(0),
     mView(nullptr)
{
   InitializeCriticalSection(&mCriticalSection);

   mView = new CView(nullptr, this);
   mView->show();

   QWidget::connect (mView, &CView::loadNextPageSignal, this, &CController::loadNextPageSlot);
   loadImages();
   mOffset += mNumberOfImagesOnPage;
   mView->showImages();
//   loadImages();
//   emit mView->loadFinishedSignal();
//   mOffset += mNumberOfImagesOnPage;
}

CController::~CController()
{
   DeleteCriticalSection(&mCriticalSection);
   delete mView;
   delete mDeviantArtParser;
}

void CController::loadFullSizePicture(std::shared_ptr<CViewImage> picture)
{
   EnterCriticalSection(&mCriticalSection);
   (*picture).setFullSizeData(mRequester.get((*picture).getFullSizeLink()));
   LeaveCriticalSection(&mCriticalSection);
}

void CController::loadImages()
{
   EnterCriticalSection(&mCriticalSection);
   QString htmlPage = mRequester.get(QString("http://www.deviantart.com/browse/all/") +
                                     QString("?offset=") +
                                     QString::number(mOffset));
   LeaveCriticalSection(&mCriticalSection);
   QList<std::shared_ptr<CViewImage>> imagesList;
   mDeviantArtParser->parseImagesFromBrowsePage(htmlPage,
                                               imagesList,
                                               mNumberOfImagesOnPage);
   QList<QString> previewURLs;
   for(auto it: imagesList)
   {
      previewURLs.push_back((*it).getPreviewURL());
   }

   QList<QPair<QByteArray, QString>> previewData;
   previewData = mRequester.getAsync(previewURLs);
   Q_ASSERT(previewData.size()==imagesList.size());

   for(auto data: previewData)
   {
      for(auto pImage: imagesList)
      {
         if(data.second == (*pImage).getPreviewURL())
         {
            (*pImage).setPreviewData(data.first);
            qDebug () << "setPrevData";
            break;
         }
      }
   }
   for (auto pImage: imagesList)
   {
      mView->addImage(pImage);
   }
}

void CController::loadNextPageSlot()
{
   mView->clearOldestList();
   loadImages();
   mOffset += mNumberOfImagesOnPage;
   emit mView->loadFinishedSignal();
}

