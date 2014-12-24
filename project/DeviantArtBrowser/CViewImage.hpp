#ifndef CVIEWIMAGE_HPP
#define CVIEWIMAGE_HPP

#include <QWidget>
#include <QImage>
#include <QPushButton>
#include <QSize>

class CViewImage : public QWidget
{
   Q_OBJECT

   const size_t mID;
   QImage mImagePreview;
   QImage mImageFullSize;

   const QString mPreviewURL;
   const QString mFullSizeURL;
   const QString mSourcePageURL;

   QPushButton mSaveButton;
   QPushButton mSourceURLButton;
   QSize mButtonsSize;
   static size_t mCurrentID;
   static size_t IDGenerator();

   QPoint mClickTrackPoint;
public:
   explicit CViewImage(QString previewURL, QString fullSizeURL, QString sourcePageURL, QWidget *parent = 0);

   const QString& getFullSizeLink() const;
   const QString& getSourcePageLink() const;
   const QString& getPreviewURL() const;
   const QImage &getFullSizeImage() const;

   void setFullSizeData (const QByteArray& data);
   void setPreviewData (const QByteArray& data);

   size_t getID() const;
signals:
   void showFullSizePictureSignal(size_t id);

public slots:
   void saveButtonPressed();
   void sourceURLButtonPressed();
   void showFullSizeImage();

   // QWidget interface
protected:
   void paintEvent(QPaintEvent *);
   void mousePressEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);
   void resizeEvent(QResizeEvent *);
   QSize imageAreaSize();
};

inline size_t CViewImage::IDGenerator()
{
   return mCurrentID++;
}

inline const QString &CViewImage::getFullSizeLink() const
{
   return mFullSizeURL;
}

inline const QString &CViewImage::getSourcePageLink() const
{
   return mSourcePageURL;
}

inline const QString &CViewImage::getPreviewURL() const
{
   return mPreviewURL;
}

inline const QImage& CViewImage::getFullSizeImage() const
{
   return mImageFullSize;
}

inline void CViewImage::setFullSizeData(const QByteArray &data)
{
   mImageFullSize = QImage(QImage::fromData(data));
}

inline void CViewImage::setPreviewData(const QByteArray &data)
{
   mImagePreview = QImage(QImage::fromData(data));
}

inline size_t CViewImage::getID() const
{
   return mID;
}

#endif // CVIEWIMAGE_HPP
