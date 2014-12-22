#include "CDeviantArtParser.hpp"
#include <QWebPage>
#include <QEventLoop>
#include <QWebElementCollection>
#include <QWebFrame>
#include <memory>
CDeviantArtParser::CDeviantArtParser()
{
}

bool CDeviantArtParser::parseImagesFromBrowsePage(QString &page, QList<std::shared_ptr<CImageData>> &images)
{
   bool ret = true;

   QWebPage webPage;
   QEventLoop load;
   QObject::connect(&webPage, &QWebPage::loadFinished, &load, &QEventLoop::quit);
   webPage.mainFrame()->setHtml(page);
   load.exec();
   QWebElement allPage = webPage.mainFrame()->documentElement();
   QWebElementCollection pictures = allPage.findAll("span[class=\"tt-fh-tc\"]");
//   int count = 0;
//   bool isPictures = false;
   QString fullSizeUrl;
   QString previewUrl;
   QString sourceUrl;
   foreach (auto it, pictures)
   {
      if(it.findFirst("a").hasAttribute("data-super-img"))
      {
         if(it.findFirst("a").hasAttribute("href"))
         {
            sourceUrl = it.findFirst("a").attribute("href");
         }
         fullSizeUrl = it.findFirst("a").attribute("data-super-img");

         if(it.findFirst("a").hasAttribute("data-super-full-img"))
         {
            fullSizeUrl = it.findFirst("a").attribute("data-super-full-img");
         }

         if(it.findFirst("img").hasAttribute("src"))
         {
            previewUrl = it.findFirst("img").attribute("src");
            //images.push_back(QPair<QString, QString> (fullSizeUrl, previewUrl));
         }
         else
         {
            ret = false;
            break;
            ///<@todo make error string; error: "cannot parse preview image from tag image and attribut src"
         }
         images.push_back(std::make_shared<CImageData> (CImageData(previewUrl, fullSizeUrl, sourceUrl)));
      }

   }
   return ret;
}