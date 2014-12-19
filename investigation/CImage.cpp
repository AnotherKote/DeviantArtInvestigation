#include "CImage.hpp"
#include <QPainter>
#include <QDebug>
#include <mainwindow.h>


int CImage::getId() const
{
   return id;
}

void CImage::setId(int value)
{
   id = value;
}
CImage::CImage(QWidget *parent) :
   QWidget(parent)
{
}

void CImage::setImage(QImage picture)
{
   image = picture;
}

void CImage::paintEvent(QPaintEvent *)
{
   QPainter p;
   p.begin(this);
   p.drawImage(0,0, image);
   this->resize(image.size());
   qDebug() << "my own paint Event" << id;
}

void CImage::mousePressEvent(QMouseEvent *)
{
   emit dynamic_cast<MainWindow*>(parentWidget())->showFullSize(id);
}
