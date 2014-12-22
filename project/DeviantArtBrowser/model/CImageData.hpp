#ifndef CIMAGEDATA_HPP
#define CIMAGEDATA_HPP

#include <QByteArray>
#include <QString>
class CImageData
{
   const size_t mID;
   const QString mPreviewURL;
   const QString mFullSizeURL;
   const QString mSourcePageURL;
   QByteArray mPreviewData;
   QByteArray mFullSizeData;

   static size_t mCurrentID;
   static size_t IDGenerator();

public:
   CImageData(QString previewData,
              QString fullSizeURL,
              QString sourcePageURL);

   const QByteArray& getPreview() const;
   const QByteArray& getFullSizeData() const;
   const QString& getFullSizeLink() const;
   const QString& getSourcePageLink() const;
   const QString& getPreviewLink() const;
   void setFullSizeData (const QByteArray& data);
   void setPreviewData (const QByteArray& data);
};

inline size_t CImageData::IDGenerator()
{
   return mCurrentID++;
}

inline const QByteArray &CImageData::getPreview() const
{
   return mPreviewData;
}

inline const QString &CImageData::getFullSizeLink() const
{
   return mFullSizeURL;
}

inline const QString &CImageData::getSourcePageLink() const
{
   return mSourcePageURL;
}

inline const QString &CImageData::getPreviewLink() const
{
   return mPreviewURL;
}

inline void CImageData::setFullSizeData(const QByteArray &data)
{
   mFullSizeData = data;
}

inline void CImageData::setPreviewData(const QByteArray &data)
{
   mPreviewData = data;
}

#endif // CIMAGEDATA_HPP
