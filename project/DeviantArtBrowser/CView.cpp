#include "CView.hpp"
#include "ui_CView.h"

CView::CView(QWidget *parent, CController *cont/*, CModel *model*/) :
   QMainWindow(parent),
   ui(new Ui::CView),
//   mModel(model),
   mController(cont),
   mChildsAmountHorizontal(4),
   mChildsAmountVertical(4),
   mButtonsHeight(50)
{
   ui->setupUi(this);
//   setCentralWidget(this);
   connect (this, &CView::loadFinishedSignal, this, &CView::displayImagesSlot);
}

CView::~CView()
{
   delete ui;
}

void CView::addImage(std::shared_ptr<CViewImage> image)
{
   mImagesToShow.push_back(image);
}

void CView::displayImagesSlot()
{
   int count = 0;
   int x = 0, y = 0;
   for (auto pImage: mImagesToShow)
   {
      (*pImage).setParent(this);
      (*pImage).show();
      (*pImage).setGeometry(x * mChildWidth, y * mChildHeight + mButtonsHeight, mChildWidth, mChildHeight);
      count++;
      if(x == mChildsAmountHorizontal - 1)
      {
         y++;
         x = 0;
      } else
      {
         x++;
      }
      if(y == mChildsAmountVertical)
      {
         break;
      }
      qDebug() << " show " << count << " of " << mImagesToShow.size() << " " << x * mChildWidth << " " << y * mChildHeight + mButtonsHeight;
   }
   update();
}

void CView::paintEvent(QPaintEvent *)
{
}

void CView::resizeEvent(QResizeEvent *)
{
   mChildHeight = (this->height() - mButtonsHeight)/mChildsAmountVertical;
   mChildWidth = this->width()/mChildsAmountHorizontal;
   mButtonsHeight = height() * 0.05;
   int x = 0; int y = 0;
   for (auto pImage: mImagesToShow)
   {
      (*pImage).setGeometry(x * mChildWidth, y * mChildHeight + mButtonsHeight, mChildWidth, mChildHeight);
      if(x == mChildsAmountHorizontal - 1)
      {
         y++;
         x = 0;
      } else
      {
         x++;
      }
      if(y == mChildsAmountVertical)
      {
         break;
      }
   }
}

