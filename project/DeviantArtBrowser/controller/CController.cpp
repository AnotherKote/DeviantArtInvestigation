#include "CController.hpp"

CController::CController()
   : mNumberOfImagesOnPage(0),
     mOffset(0),
     mModel(new CModel()),
     mView(nullptr)
{
   mView = new CView(nullptr, this, mModel);
}
