#ifndef CMODEL_H
#define CMODEL_H

#include <QList>
#include "CImageData.hpp"

class CModel
{
   QList<CImageData> mImageList;
   size_t mDeletedNumber;
public:
   CModel();

   void addImage(QByteArray previewData,
                 QString fullSizeURL,
                 QString sourcePageURL);
   void deleteFromBeginOfList(size_t amount);
   const QList<CImageData>& getData(size_t offset, size_t number) const;
   QString getFullSizeURL(size_t id) const;
   QString getSourcePageURL(size_t id) const;
   void setFullImageData(QByteArray data, size_t id);

};

#endif // CMODEL_H
