#ifndef CIMAGEDATA_HPP
#define CIMAGEDATA_HPP

#include <QByteArray>
#include <QString>
class CImageData
{
   const size_t mID;
   const QByteArray mPreviewData;
   const QString mFullSizeURL;
   const QString mSourcePageURL;
   QByteArray mFullSizeData;

   static size_t IDGenerator();
   static size_t current_id;
public:
   CImageData(QByteArray previewData,
              QString fullSizeURL,
              QString sourcePageURL);

   const QByteArray& getPreview() const;
   const QByteArray& getFullSizeData() const;
   const QString& getFullSizeLink() const;
   const QString& getSourcePageLink() const;
   void setFullSizeData (const QByteArray& data);

};

inline size_t CImageData::IDGenerator()
{
   return current_id++;
}

#endif // CIMAGEDATA_HPP
