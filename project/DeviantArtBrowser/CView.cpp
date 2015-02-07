#include "CView.hpp"
#include "ui_CView.h"
#include "CFullSizeView.hpp"
#include <QMessageBox>

CView::CView(QWidget *parent, CController *cont) :
   QMainWindow(parent),
   ui(new Ui::CView),
   mController(cont),
   mChildsAmountHorizontal(4),
   mChildsAmountVertical(4),
   mButtonsHeight(50),
   mCanShowNextPage(false),
   mCurrentFullSizeImage(nullptr)
{
   ui->setupUi(this);

   setWindowIcon(QIcon("Deviantart_logo.png"));
   setWindowTitle("Devart browser");

   connect (this, &CView::loadFinishedSignal, this, &CView::displayImagesSlot);
//   setStyleSheet("background:transparent;");
//   setAttribute(Qt::WA_TranslucentBackground);
   //setWindowsFlags(Qt::FramelessWindowHint);
   mNextButton.setParent(this);
   mNextButton.setText("Next");
   mNextButton.setToolTip("Next page");
   mNextButton.setShortcut(Qt::Key_Alt + Qt::Key_Right);
   mNextButton.setEnabled(mCanShowNextPage);

   mPrevButton.setParent(this);
   mPrevButton.setText("Prev");
   mPrevButton.setToolTip("Previous page");
   mPrevButton.setShortcut(Qt::Key_Alt + Qt::Key_Left);

   connect(&mNextButton, &QPushButton::released, this, &CView::nextButtonPressed);
   connect(&mPrevButton, &QPushButton::released, this, &CView::previousButtonPressed);
   connect(this, &CView::showFullSizePictureSignal, this, &CView::showFullSizePictureSlot);
   connect(this, &CView::openSourcePageSignal, this, &CView::openSourcePageSlot);
   connect(this, &CView::saveFullSizePictureSignal, this, &CView::saveFullSizePictureSlot);
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
   mNextButton.setEnabled(mCanShowNextPage);
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
   mNextButton.setEnabled(mCanShowNextPage);
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
//   qDebug() << "prev";
}

void CView::showFullSizePictureSlot(size_t ID)
{
   if(mCanShowNextPage)
   {
      this->setEnabled(false);
      if(mCurrentFullSizeImage != nullptr)
      {
         delete mCurrentFullSizeImage;
      }
      for(auto it: mImagesToShow[mCurrentList])
      {
         if((*it).getID() == ID)
         {
            if((*it).getFullSizeImage().isNull())
            {
               mController->loadFullSizePicture(it);
            }
            mCurrentFullSizeImage = new CFullSizeView((*it).getFullSizeImage(), nullptr);
            connect(mCurrentFullSizeImage, &QDialog::finished, this, &CView::fullSizeDestroyed);
            mCurrentFullSizeImage->show();
            break;
         }
      }
   } else
   {
      ///<@todo add ID to querry
   }
}

void CView::fullSizeDestroyed(int)
{
   this->setEnabled(true);
}

void CView::openSourcePageSlot(size_t ID)
{
   for(auto it: mImagesToShow[mCurrentList])
   {
      if((*it).getID() == ID)
      {
         emit mController->openSourcePageSignal((*it).getSourcePageLink());
         break;
      }
   }
}

void CView::saveFullSizePictureSlot(size_t ID)
{
   for(auto it: mImagesToShow[mCurrentList])
   {
      if((*it).getID() == ID)
      {
         if((*it).getFullSizeImage().isNull())
         {
            this->setEnabled(false);
            mController->loadFullSizePicture(it);
            this->setEnabled(true);
         }

         if( !(*it).saveThisImage("D:\\garbage\\") )
         {
            QMessageBox::information(this, "Error", "Cannot save image. \nFile url or file data is empty!", MB_OK);
         }
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

