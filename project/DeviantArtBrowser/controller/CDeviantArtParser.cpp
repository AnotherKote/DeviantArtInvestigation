#include "CDeviantArtParser.hpp"
//#include <QWebPage>
#include <QEventLoop>
//#include <QWebElementCollection>
//#include <QWebFrame>
#include <memory>
#include <QRegularExpression>
#include <QRegExp>

CDeviantArtParser::CDeviantArtParser()
{
}
#include <QDebug>
#include <fstream>
bool CDeviantArtParser::parseImagesFromBrowsePage(QString &page,
                                                  QList<std::shared_ptr<CViewImage>> &images,
                                                  const size_t count)
{
   bool ret = true;

   ///
   /// \brief dataList container contains (example):
   ///
   /// <span class="tt-fh-tc" style="width: 302px;">
   ///   <span class="shadow" >
   ///      <a class="thumb"
   ///
   ///         href="http://yuumei.deviantart.com/art/Into-The-Storm-509799320"  //source link
   ///
   ///         title="Into The Storm by yuumei, Jan 26, 2015 in Digital Art &gt; Drawings &amp; Paintings &gt; Landscapes &amp; Scenery"

   ///         data-super-img="http://th05.deviantart.net/fs71/PRE/f/2015/026/7/9/into_the_storm_by_yuumei-d8firo8.jpg" // full size img if no data-super-full-img exist

   ///         data-super-width="1264"
   ///         data-super-height="632"
   ///         data-super-transparent="false"
   ///
   ///         data-super-full-img="http://fc05.deviantart.net/fs71/f/2015/026/7/9/into_the_storm_by_yuumei-d8firo8.jpg" // full size img

   ///         data-super-full-width="1500"
   ///         data-super-full-height="750">
   ///       <i></i>
   ///         <img width="300" height="150"
   ///              alt="Into The Storm by yuumei"
   ///              src="http://th06.deviantart.net/fs71/200H/f/2015/026/7/9/into_the_storm_by_yuumei-d8firo8.jpg"  // preview img
   ///              data-src="http://th06.deviantart.net/fs71/200H/f/2015/026/7/9/into_the_storm_by_yuumei-d8firo8.jpg">
   ///       </a>
   ///   </span>

   QRegularExpression regForDataContainer("(<span class=\"tt-fh-tc\")(.*?)(<span class=\"details\")"); //   QRegExp img("(data-super(|-full)-img=\")(.*\")"); /*"((data-super(|-full)-img=)\")(.*?\")"*/
   int offset = 0;
   QRegularExpressionMatch match;
   QStringList dataList;
//   qDebug() << "AHTUNG";
//   std::ofstream stream;
//   stream.open("D:\\garbage\\page.log.dev.pars.html");
//   stream << page.toStdString();
//   stream.close();
//   qDebug() << "AHTUNG";
   for (;;)
   {
      match = regForDataContainer.match(page, offset);
      if(!match.hasMatch())
      {
         break;
      }
//      qDebug() << match.capturedTexts();
      dataList.push_back( match.captured() );
      offset = page.indexOf( regForDataContainer, offset );
      offset += match.captured().length();
   };

   qDebug() << dataList.size();

   size_t i = 0;
   if (dataList.size() == 0)
   {
      ret = false;
   }  else
   {
      QRegularExpression regForHref ("(href=\")(.*?)(\")");
      QRegularExpression regForSuperImage ("(data-super-img=\")(.*?)(\")");
      QRegularExpression regForSuperFullImage ("(data-super-full-img=\")(.*?)(\")");
      QRegularExpression regForPreview ("(data-src=\")(.*?)(\")");

      QString fullSizeUrl;
      QString previewUrl;
      QString sourceUrl;

      for (auto &it: dataList)
      {
         match = regForHref.match(it);
         if ( match.hasMatch() )
         {
            sourceUrl = match.capturedTexts()[2];
         }

         match = regForPreview.match(it);
         if ( match.hasMatch() )
         {
            previewUrl = match.capturedTexts()[2];
         }

         if (it.contains("full"))
         {
            match = regForSuperFullImage.match(it);
            if (match.hasMatch())
            {
               fullSizeUrl = match.capturedTexts()[2];
            }
         } else
         {
            match = regForSuperImage.match(it);
            if (match.hasMatch())
            {
               fullSizeUrl = match.capturedTexts()[2];
            }
         }
         if ( !fullSizeUrl.isEmpty() && !previewUrl.isEmpty() && !sourceUrl.isEmpty())
         {
            images.push_back(std::shared_ptr<CViewImage>(new CViewImage(previewUrl, fullSizeUrl, sourceUrl)));
         }

         if(i++ > count)
         {
            break;
         }
      }
   }

   return ret;
}
