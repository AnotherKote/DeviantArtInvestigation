#ifndef CVIEW_HPP
#define CVIEW_HPP

#include <QMainWindow>
#include "CViewImage.hpp"
#include "controller/CController.hpp"
#include "model/CModel.hpp"

namespace Ui {
   class CView;
}
class CController;
class CView : public QMainWindow
{
   Q_OBJECT

private:
   QList<CViewImage> mImagesToShow;
   size_t mNumberOfImagesOnPage;
   const CModel *const mModel;
   CController *const mController;

public:
   explicit CView(QWidget *parent, CController *cont, CModel *model);
   ~CView();

private:
   Ui::CView *ui;
};

#endif // CVIEW_HPP
