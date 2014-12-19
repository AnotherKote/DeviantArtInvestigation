#ifndef CVIEWIMAGE_HPP
#define CVIEWIMAGE_HPP

#include <QWidget>
#include <QImage>
#include <QPushButton>

class CViewImage : public QWidget
{
   Q_OBJECT

   size_t mID;
   QImage mImage;
   QPushButton mSaveButton;
   QPushButton mSourceURLButton;

public:
   explicit CViewImage(QWidget *parent = 0);
   void setData (QImage image, size_t id);

signals:

public slots:
   void saveButtonPressed();
   void sourceURLButtonPressed();
   void showFullSizeImage();
};

inline void CViewImage::setData(QImage image, size_t id)
{
   mImage = image;
   mID = id;
}

#endif // CVIEWIMAGE_HPP
