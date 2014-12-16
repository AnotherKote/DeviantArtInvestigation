#include "imageviewer.hpp"
#include <QDebug>

imageViewer::imageViewer(QWidget *parent) :
   QWidget(parent)
{
   mImageLabel = new QLabel;
   mImageLabel->setBackgroundRole(QPalette::Base);
   mImageLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
   mImageLabel->setScaledContents(true);

   mImageTip = new QLabel;
   mImageTip->setBackgroundRole(QPalette::Base);
   mImageTip->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   mImageTip->setScaledContents(true);
}

void imageViewer::setImage(QImage image)
{
   mImage = image;
   mImageLabel->setPixmap(QPixmap::fromImage(image.scaled(50,50, Qt::KeepAspectRatio)));
   mImageLabel->move(100,100);
   mImageTip->setPixmap(QPixmap::fromImage(image));
   mImageLabel->move(0,0);
}
