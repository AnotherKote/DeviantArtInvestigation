#ifndef CMODEL_H
#define CMODEL_H

#include <QList>
#include <memory>
#include "CViewImage.hpp"
#include "CViewImage.hpp"

class CModel
{
   QList<std::shared_ptr<CViewImage>> mImageList;
   size_t mDeletedNumber;
public:
   CModel();

   void addImage(QByteArray previewData,
                 QString fullSizeURL,
                 QString sourcePageURL);
   void addImage (std::shared_ptr<CViewImage> pImage);
   void deleteFromBeginOfList(size_t amount);
   const QList<std::shared_ptr<CViewImage>>& getData(size_t offset, size_t number) const;
   QString getFullSizeURL(size_t id) const;
   QString getSourcePageURL(size_t id) const;
   void setFullImageData(QByteArray data, size_t id);

};

inline void CModel::addImage(std::shared_ptr<CViewImage> pImage)
{
   mImageList.push_back(pImage);
}

#endif // CMODEL_H
