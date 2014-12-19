#include "CView.hpp"
#include "ui_CView.h"

CView::CView(QWidget *parent, CController *cont, CModel *model) :
   QMainWindow(parent),
   ui(new Ui::CView),
   mModel(model),
   mController(cont)
{
   ui->setupUi(this);
}

CView::~CView()
{
   delete ui;
}
