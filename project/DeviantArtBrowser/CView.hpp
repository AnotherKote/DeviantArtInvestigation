#ifndef CVIEW_HPP
#define CVIEW_HPP

#include <QMainWindow>
#include "CViewImage.hpp"
#include "controller/CController.hpp"
//#include "model/CModel.hpp"

namespace Ui {
   class CView;
}
class CController;
class CView : public QMainWindow
{
   Q_OBJECT

private:
   Ui::CView *ui;

   QList<std::shared_ptr<CViewImage>> mImagesToShow;
   size_t mNumberOfImagesOnPage;
//   const CModel *const mModel;
   CController *const mController;

   size_t mChildsAmountHorizontal;
   size_t mChildsAmountVertical;

   size_t mChildWidth;
   size_t mChildHeight;
   size_t mButtonsHeight;

public:
   explicit CView(QWidget *parent, CController *cont/*, CModel *model*/);
   ~CView();
   void addImage(std::shared_ptr<CViewImage> image);
private slots:
   void displayImagesSlot();

signals:
   void loadFinishedSignal();


   // QWidget interface
protected:
   void paintEvent(QPaintEvent *);
   void resizeEvent(QResizeEvent *);
};

#endif // CVIEW_HPP
