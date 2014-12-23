#include "CController.hpp"

CController::CController()
   : mDeviantArtParser(new CDeviantArtParser),
     mNumberOfImagesOnPage(16), ///<@todo remove magic numbers
     mOffset(0),
     mView(nullptr)
{
   mView = new CView(nullptr, this);
   mView->show();
}

CController::~CController()
{
   delete mView;
   delete mDeviantArtParser;
}

void CController::loadNextPage()
{
   QString htmlPage = mRequester.get(QString("http://www.deviantart.com/browse/all/") +
                                     QString("?offset=") +
                                     QString::number(mOffset));
   QList<std::shared_ptr<CViewImage>> imagesList;
   mDeviantArtParser->parseImagesFromBrowsePage(htmlPage,
                                               imagesList,
                                               mNumberOfImagesOnPage,
                                               mView);
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
            break;
         }
      }
   }
   for (auto pImage: imagesList)
   {
      mView->addImage(pImage);
   }

   emit mView->loadFinishedSignal();
}

