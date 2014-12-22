#include "CView.hpp"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <memory>
#include "controller/CDeviantArtParser.hpp"
#include"controller/CRequester.hpp"
#include "model/CImageData.hpp"

void CRequesterTesterGet()
{
   qDebug() << "Requester Test Start";

   CRequester a;
   QByteArray pic = a.get("http://fc06.deviantart.net/fs70/i/2012/171/e/2/mlp_fim___mane_six_by_galaxyart-d53o02k.png");
   QFile picture;
   QDir dir;
   dir.setCurrent("D:\\MyOwnProject\\DeviantArtInvestigation\\trunk");
   if(!dir.exists("Test"))
   {
      dir.mkdir("Test");
   }
   dir.setCurrent("Test");
   picture.setFileName("mlp_fim___mane_six_by_galaxyart-d53o02k.png");
   picture.open(QIODevice::WriteOnly);

   picture.write(pic);
   picture.close();

   qDebug() << "Requester Test End";
}

void CRequesterTesterGetAsync()
{
   qDebug() << "RequesterAsync Test Start";

   CRequester a;
   QFile links;
   QDir dir;

   dir.setCurrent("D:\\MyOwnProject\\DeviantArtInvestigation\\trunk\\Test");

   links.setFileName("links.txt");
   links.open(QIODevice::ReadOnly | QIODevice::Text);
   QList<QString> urls;
   while(!links.atEnd())
   {
      urls.append(QString(links.readLine()).remove("\n"));
   }
   //urls.append("http://fc06.deviantart.net/fs70/i/2012/171/e/2/mlp_fim___mane_six_by_galaxyart-d53o02k.png");
   QList<QPair<QByteArray,QString>> result;
   result = a.getAsync(urls);

   Q_ASSERT(result.size() == urls.size());

   for (auto pathIt = urls.begin(); pathIt != urls.end(); pathIt++)
   {
      (*pathIt).remove(0, (*pathIt).lastIndexOf("/") + 1);
   }
   links.close();
   QFile picture;
   dir.setCurrent("D:\\MyOwnProject\\DeviantArtInvestigation\\trunk\\Test");
   dir.setCurrent("pcr");
   for (auto dataIt = result.begin(); dataIt != result.end(); dataIt++)
   {
      picture.setFileName((*dataIt).second.remove(0, (*dataIt).second.lastIndexOf("/") + 1));
      picture.open(QIODevice::WriteOnly);
      picture.write((*dataIt).first);
      picture.close();
   }

   qDebug() << "RequesterAsync Test End";
}

void CParserTest ()
{
   CDeviantArtParser par;
   CRequester r;
   QString page = r.get("http://doncellasuicide.deviantart.com/gallery/");
   QList<std::shared_ptr<CImageData>> list;
   par.parseImagesFromBrowsePage(page, list);

   for(auto it: list)
   {
      qDebug() << (*it).getFullSizeLink();
      qDebug() << (*it).getPreviewLink();
      qDebug() << (*it).getSourcePageLink();
   }

}

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   CParserTest();

   exit(0);
   return a.exec();
}
