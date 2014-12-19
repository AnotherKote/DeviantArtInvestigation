#include "CImageData.hpp"

CImageData::CImageData(QByteArray previewData, QString fullSizeURL, QString sourcePageURL)
   : mPreviewData(previewData),
     mFullSizeURL(fullSizeURL),
     mSourcePageURL(sourcePageURL),
     mID(IDGenerator())
{
}
