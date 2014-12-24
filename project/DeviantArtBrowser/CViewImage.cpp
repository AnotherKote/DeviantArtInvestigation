#include <QMouseEvent>
#include "CViewImage.hpp"
#include <QPainter>
#include <QDebug>
size_t CViewImage::mCurrentID = 0;

CViewImage::CViewImage(QString previewURL, QString fullSizeURL, QString sourcePageURL, QWidget *parent) :
   QWidget(parent),
   mID(IDGenerator()),
   mPreviewURL(previewURL),
   mFullSizeURL(fullSizeURL),
   mSourcePageURL(sourcePageURL),
   mButtonsSize(QSize(50, 20)),
   mIsPreview(true)
{
   mSaveButton.setParent(this);
   mSaveButton.setText("Save");
   mSaveButton.setToolTip("Save this image");

   mSourceURLButton.setParent(this);
   mSourceURLButton.setText("Source");
   mSourceURLButton.setToolTip("Open source page in browser");

   connect(&mSaveButton, &QPushButton::released, this, &CViewImage::saveButtonPressed);
   connect(&mSourceURLButton, &QPushButton::released, this, &CViewImage::sourceURLButtonPressed);
}

void CViewImage::saveButtonPressed()
{

}

void CViewImage::sourceURLButtonPressed()
{

}

void CViewImage::showFullSizeImage()
{

}

void CViewImage::paintEvent(QPaintEvent *)
{
   QPainter p;
   p.begin(this);
   if(mIsPreview)
   {
      QSize previewSize = mImagePreview.size().scaled(imageAreaSize(), Qt::KeepAspectRatio);

      int x = (width() - previewSize.width())/2;
      int y = (height() - previewSize.height() - mButtonsSize.height())/2;

      p.drawImage(x,y, mImagePreview.scaled(imageAreaSize(),Qt::KeepAspectRatio));
   }else
   {
      resize(mImageFullSize.size());
      p.drawImage(0,0,mImageFullSize);
   }
}

void CViewImage::mousePressEvent(QMouseEvent *event)
{
   mClickTrackPoint = event->pos() ;
}

#include "CView.hpp"
void CViewImage::mouseReleaseEvent(QMouseEvent *event)
{
   if(mClickTrackPoint == event->pos())
   {
      emit dynamic_cast<CView*>(parentWidget())->showFullSizePictureSignal(mID);
   }
}

void CViewImage::resizeEvent(QResizeEvent *)
{
   mButtonsSize.setHeight(height()*0.1);
   mButtonsSize.setWidth(width()/2);
   mSaveButton.setGeometry(0, height() - mButtonsSize.height(), mButtonsSize.width(), mButtonsSize.height());
   mSourceURLButton.setGeometry(width()/2, height() - mButtonsSize.height(), mButtonsSize.width(), mButtonsSize.height());
}

QSize CViewImage::imageAreaSize()
{
   return QSize(width(), height()-mButtonsSize.height());
}

