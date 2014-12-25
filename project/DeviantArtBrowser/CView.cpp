#include "CView.hpp"
#include "ui_CView.h"
#include "CFullSizeView.hpp"

CView::CView(QWidget *parent, CController *cont) :
   QMainWindow(parent),
   ui(new Ui::CView),
   mController(cont),
   mChildsAmountHorizontal(4),
   mChildsAmountVertical(4),
   mButtonsHeight(50),
   mCanShowNextPage(false)
{
   ui->setupUi(this);
   connect (this, &CView::loadFinishedSignal, this, &CView::displayImagesSlot);
//   setStyleSheet("background:transparent;");
//   setAttribute(Qt::WA_TranslucentBackground);
   //setWindowFlags(Qt::FramelessWindowHint);
   mNextButton.setParent(this);
   mNextButton.setText("Next");
   mNextButton.setToolTip("Next page");
   mNextButton.setShortcut(Qt::Key_Alt + Qt::Key_Right);
   mNextButton.hide();

   mPrevButton.setParent(this);
   mPrevButton.setText("Prev");
   mPrevButton.setToolTip("Previous page");
   mPrevButton.setShortcut(Qt::Key_Alt + Qt::Key_Left);

   connect(&mNextButton, &QPushButton::released, this, &CView::nextButtonPressed);
   connect(&mPrevButton, &QPushButton::released, this, &CView::previousButtonPressed);
   connect(this, &CView::showFullSizePictureSignal, this, &CView::showFullSizePictureSlot);
}

CView::~CView()
{
   delete ui;
}

void CView::addImage(std::shared_ptr<CViewImage> image)
{
   mImagesToShow[mCurrentList + 1].push_back(image);
}

void CView::hideImages()
{
   for(auto pImage: mImagesToShow[mCurrentList])
   {
      (*pImage).hide();
   }
}

void CView::clearOldestList()
{
   mImagesToShow[mCurrentList + 1].clear();
}

void CView::showImages()
{
   hideImages();
   mCurrentList++;
   mCanShowNextPage = false;
   mNextButton.hide();
   int count = 0;
   size_t row = 0, column = 0;
   for (auto pImage: mImagesToShow[mCurrentList])
   {
      (*pImage).setParent(this);
      (*pImage).show();
      (*pImage).setGeometry(row * mChildWidth, column * mChildHeight + mButtonsHeight, mChildWidth, mChildHeight);
      count++;
      if(row == mChildsAmountHorizontal - 1)
      {
         column++;
         row = 0;
      } else
      {
         row++;
      }
      if(column == mChildsAmountVertical)
      {
         break;
      }
      //qDebug() << " show " << count << " of " << mImagesToShow.size() << " " << row * mChildWidth << " " << column * mChildHeight + mButtonsHeight;
   }
   update();

   emit loadNextPageSignal();
}

void CView::displayImagesSlot()
{
   mCanShowNextPage = true;
   mNextButton.show();
}

void CView::nextButtonPressed()
{
   if(mCanShowNextPage)
   {
      showImages();
   }
}

void CView::previousButtonPressed()
{
   qDebug() << "prev";
}

void CView::showFullSizePictureSlot(size_t ID)
{
   if(mCurrentFullSizeImage != nullptr)
   {
      delete mCurrentFullSizeImage;
   }
   for(auto it: mImagesToShow[mCurrentList])
   {
      if((*it).getID() == ID)
      {
         mController->loadFullSizePicture(it);
         mCurrentFullSizeImage = new CFullSizeView((*it).getFullSizeImage(), 0);
         mCurrentFullSizeImage->show();
         break;
      }
   }
}

void CView::paintEvent(QPaintEvent *)
{
}

void CView::resizeEvent(QResizeEvent *)
{
   mChildHeight = (this->height() - mButtonsHeight)/mChildsAmountVertical;
   mChildWidth = this->width()/mChildsAmountHorizontal;
   mButtonsHeight = height() * 0.05;
   size_t row = 0; size_t column = 0;
   for (auto pImage: mImagesToShow[mCurrentList])
   {
      (*pImage).setGeometry(row * mChildWidth, column * mChildHeight + mButtonsHeight, mChildWidth, mChildHeight);
      if(row == mChildsAmountHorizontal - 1)
      {
         column++;
         row = 0;
      } else
      {
         row++;
      }
      if(column == mChildsAmountVertical)
      {
         break;
      }
   }

   mPrevButton.setGeometry(0,0, width()/3, mButtonsHeight);
   mNextButton.setGeometry(width()*2/3, 0, width()/3, mButtonsHeight);
}

