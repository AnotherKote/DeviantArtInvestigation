#ifndef CVIEW_HPP
#define CVIEW_HPP

#include <QMainWindow>
#include "CViewImage.hpp"
#include "controller/CController.hpp"
#include <QPushButton>
#include <controller/CMyCoolIterator.hpp>
#include "CFullSizeView.hpp"

namespace Ui {
   class CView;
}
class CController;
class CView : public QMainWindow
{
   Q_OBJECT

private:
   Ui::CView *ui;
   CMyCoolIterator mCurrentList;
   QList<std::shared_ptr<CViewImage>> mImagesToShow[CMyCoolIterator::MAX];
   CController *const mController;

   CFullSizeView* mCurrentFullSizeImage;

   size_t mChildsAmountHorizontal;
   size_t mChildsAmountVertical;
   size_t mChildWidth;
   size_t mChildHeight;
   size_t mButtonsHeight;
   QPushButton mNextButton;
   QPushButton mPrevButton;

   bool mCanShowNextPage;
   void hideImages();
public:
   void clearOldestList();
   void showImages();
   explicit CView(QWidget *parent, CController *cont);
   ~CView();
   void addImage(std::shared_ptr<CViewImage> image);

private slots:
   void displayImagesSlot();
   void nextButtonPressed();
   void previousButtonPressed();
   void showFullSizePictureSlot(size_t ID);

signals:
   void loadFinishedSignal();
   void loadNextPageSignal();
   void showFullSizePictureSignal(size_t ID);

protected:
   void paintEvent(QPaintEvent *);
   void resizeEvent(QResizeEvent *);
};

#endif // CVIEW_HPP
