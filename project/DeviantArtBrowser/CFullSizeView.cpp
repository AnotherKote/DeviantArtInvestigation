#include "CFullSizeView.hpp"
#include <QPainter>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

CFullSizeView::CFullSizeView(QImage image, QWidget *parent) :
   QDialog(parent, Qt::Window)
{
   setStyleSheet("background:transparent;");
   setAttribute(Qt::WA_TranslucentBackground);
   setWindowFlags(Qt::FramelessWindowHint);

   mImage = new QLabel(this);
   mImage->setBackgroundRole(QPalette::Base);
   mImage->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
   mImage->setScaledContents(true);

   int desktopW = QApplication::desktop()->width();
   int desktopH = QApplication::desktop()->height();

   if(desktopW < image.width() || desktopH < image.height())
   {
      mImage->setPixmap(QPixmap::fromImage(image.scaled(desktopW, desktopH, Qt::KeepAspectRatio)));
      resize(image.scaled(desktopW, desktopH, Qt::KeepAspectRatio).size());
   }else
   {
      mImage->setPixmap(QPixmap::fromImage(image));
      resize(image.size());
   }

   int move_to_x;
   int move_to_y;

   move_to_x = (desktopW - width())/2;
   move_to_y = (desktopH - height())/2;

   move(move_to_x, move_to_y);

}

//void CFullSizeView::paintEvent(QPaintEvent *)
//{
//   QPainter p;
//   p.begin(this);
//   p.drawImage(0,0,mImage);
//   resize(mImage.size());
//}
