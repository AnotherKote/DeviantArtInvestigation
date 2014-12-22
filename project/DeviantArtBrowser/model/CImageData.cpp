#include "CImageData.hpp"

size_t CImageData::mCurrentID = 0;

CImageData::CImageData(QString previewURL, QString fullSizeURL, QString sourcePageURL)
   : mID(IDGenerator()),
     mPreviewURL(previewURL),
     mFullSizeURL(fullSizeURL),
     mSourcePageURL(sourcePageURL)
{
}
