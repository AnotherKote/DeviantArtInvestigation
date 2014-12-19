#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//     this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint);
   button = new QPushButton("&Download", this);
   connect(button, &QPushButton::released, this, &MainWindow::buttonPressed);
   connect(this, &MainWindow::showFullSize, this, &MainWindow::buttonPressedInt);
   mImageLabel = new QLabel;
   mImageLabel->setBackgroundRole(QPalette::Base);
   mImageLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
   mImageLabel->setScaledContents(true);

   mImageTip = new QLabel;
   mImageTip->setBackgroundRole(QPalette::Base);
   mImageTip->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   mImageTip->setScaledContents(true);

   mScrollArea = new QScrollArea;
   mScrollArea->setBackgroundRole(QPalette::Dark);
   mScrollArea->setWidget(mImageLabel);

   mainWidget = new imageViewer(this);
   //setCentralWidget(mainWidget);
//   mScrollArea->setMouseTracking(true);
//   this->setMouseTracking(true);
//   mImageLabel->setMouseTracking(true);

//    setCentralWidget(mainWidget);
//    connect(mainWidget, SIGNAL(paintSignal(QPaintEvent*)), this, SLOT(centralWidgetPaintSlot(QPaintEvent*)));
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::setpixmap(QImage pixmap, bool first)
{
//   mImageLabel->setPixmap(QPixmap::fromImage(pixmap.scaled(50,50, Qt::KeepAspectRatio)));
   //mImageLabel->
   mPixmapList.append(pixmap);
//   mPixmap = pixmap;
   mainWidget->setImage(pixmap);
   mainWidget->update();
   if(first)
   {
      imageObject = new CImage(this);
      imageObject->setImage(pixmap);
      imageObject->setId(10);
      imageObject->move(0,0);
   }else
   {
      imageObject2 = new CImage(this);
      imageObject2->setImage(pixmap);
      imageObject2->setId(20);
      imageObject->move(200,0);
   }


}

void MainWindow::centralWidgetPaintSlot(QPaintEvent *)
{
   qDebug() << "mm";
}

void MainWindow::buttonPressed()
{
   qDebug() << "pressedButton";
}

void MainWindow::buttonPressedInt(int id)
{
   qDebug () << "PRESSED " << id;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
   qDebug() << "mouse";

//   mImageLabel->move(10,10);
//   mImageLabel->update();
   if(mImageLabel->underMouse())
   {
      qDebug() << "picture";
   }

}

void MainWindow::paintEvent(QPaintEvent *event)
{
//   QPainter p;
//   p.begin(this);
//   p.drawImage(0,0, mPixmap);
//   button->setGeometry(0, mPixmap.height() + 10, mPixmap.width()/3, 0);
//   this->resize(mPixmap.size());
//   this->move(200,50);
//   p.drawImage(20, 20, mPixmap.scaled(50,50, Qt::KeepAspectRatio));
   qDebug() << "paint";


}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
//   qDebug() << "show full";

//   if(mImageLabel->underMouse())
//   {
//      qDebug() << "show full picture";

//      mImageTip->setPixmap(QPixmap::fromImage(mPixmap));
//      mImageTip->adjustSize();
//      mImageTip->move(event->globalPos());
//      mImageTip->show();
//      mImageLabel->update();
//   }else
//   {
//      mImageTip->hide();

//   }
}
