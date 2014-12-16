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
   QPushButton *button = new QPushButton("&Download", this);
   button->setGeometry(20,40,300,400);

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

void MainWindow::setpixmap(QImage pixmap)
{
   mImageLabel->setPixmap(QPixmap::fromImage(pixmap.scaled(50,50, Qt::KeepAspectRatio)));
   //mImageLabel->
   mPixmap = pixmap;
   mainWidget->setImage(pixmap);
   mainWidget->update();
}

void MainWindow::centralWidgetPaintSlot(QPaintEvent *)
{
   qDebug() << "mm";
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
   qDebug() << "mouse";
//   mImageLabel->move(10,10);
//   mImageLabel->update();
//   if(mImageLabel->underMouse())
//   {
//      qDebug() << "picture";
//   }

}

void MainWindow::paintEvent(QPaintEvent *event)
{
   QPainter p;
   p.begin(this);
   p.drawImage(20, 20, mPixmap.scaled(50,50, Qt::KeepAspectRatio));
   qDebug() << "paint";


}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
   qDebug() << "show full";

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
