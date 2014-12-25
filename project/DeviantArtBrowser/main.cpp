#include <QApplication>
#include <QFile>
#include <QDir>
#include <memory>
#include "CView.hpp"
#include "controller/CDeviantArtParser.hpp"
#include "controller/CRequester.hpp"
#include "CViewImage.hpp"
#include "controller/CController.hpp"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   CController c;
   return a.exec();
}
