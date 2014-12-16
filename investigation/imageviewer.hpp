#ifndef IMAGEVIEWER_HPP
#define IMAGEVIEWER_HPP

#include <QMainWindow>
#include <QLabel>

class imageViewer : public QWidget
{
   Q_OBJECT
   QLabel *mImageLabel;
   QLabel *mImageTip;
   QImage mImage;

public:
   explicit imageViewer(QWidget *parent = 0);
   void setImage(QImage image);
};

#endif // IMAGEVIEWER_HPP
