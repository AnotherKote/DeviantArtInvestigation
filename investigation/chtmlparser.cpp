#include "chtmlparser.hpp"
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <fstream>
#include <QStringRef>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QEventLoop>

void CHTMLParser::errorMessenger(QXmlStreamReader &stream)
{
   QString errString = stream.errorString();
   errString += "\n line: " + QString::number(stream.lineNumber());
   errString += "\n column: " + QString::number(stream.columnNumber());
   QMessageBox::warning(0, "Error", errString);
}

CHTMLParser::CHTMLParser()
{
}
void stringToFile1(QString text, QString fileName)
{
    std::ofstream of("D:\\" + fileName.toStdString() + ".html");
    of << text.toStdString();
    of.close();
}

bool CHTMLParser::parseImagesFromBrowsePage(QString &page, std::deque<QPair<QString, QString>> &deque)
{
   bool ret = true;
   QWebPage webPage;
   QEventLoop load;
   QObject::connect(&webPage, &QWebPage::loadFinished, &load, &QEventLoop::quit);
   webPage.mainFrame()->setHtml(page);
   load.exec();
   QWebElement allPage = webPage.mainFrame()->documentElement();
   QWebElementCollection pictures = allPage.findAll("span[class=\"tt-fh-tc\"]");
   int count = 0;
   bool isPictures = false;
   QString fullSizeUrl;
   QString previewUrl;
   foreach (auto it, pictures)
   {
      if(it.findFirst("a").hasAttribute("data-super-img"))
      {
         if(it.findFirst("a").hasAttribute("data-super-full-img"))
         {
            fullSizeUrl = it.findFirst("a").attribute("data-super-full-img");
         }

         fullSizeUrl = it.findFirst("a").attribute("data-super-img");

         if(it.findFirst("img").hasAttribute("src"))
         {
            previewUrl = it.findFirst("img").attribute("src");
            deque.push_back(QPair<QString, QString> (fullSizeUrl, previewUrl));
         }
         else
         {
            ret = false;
            break;
            ///<@todo make error string; error: "cannot parse preview image from tag image and attribut src"
         }
      }

   }
   return ret;
}


void CHTMLParser::removeBetweenIncluding(QString &text, QString start_text, QString end_text)
{
   while (text.contains(start_text))
   {
      int start_index = text.indexOf(start_text);
      int end_index = text.indexOf(end_text);
      end_index = end_index + end_text.size();
      int length = end_index - start_index;
      qDebug() << text.section("", start_index, length);
      text.remove(start_index, length);
   }
}

void CHTMLParser::getBetweenIncluding(QString &text, QString left_text, QString right_text)
{
   QString buf;
   int end_index = 0;
   qDebug () << text.count("<a");
   qDebug () << text.count("</a>");
   removeBetweenIncluding(text, "<svg", "</svg>");
   text.replace('&', "&amp;");
   text.replace("=oh-l", "=\"oh-l\"");
   text.replace("\"34\"onclick", "\"34\" onclick");
   while (true)
   {
      int start_index = text.indexOf(left_text, end_index);
      end_index = text.indexOf(right_text, start_index);
      if (end_index == -1)
      {
         break;
      }
      //qDebug() << "startIndex = " << text[start_index] << text[start_index+1] << " endIndex = " << text[end_index];
      end_index = end_index + right_text.size();
      int length = end_index - start_index;
      QString section = text.mid(start_index, length);
      //qDebug() << section;
      buf.append(section);
   }
   text.swap(buf);
   text.prepend("<tag>");
   text.append("</tag>");
}

void CHTMLParser::removeScriptAndComment(QString &html)
{

   //    html.remove(QRegularExpression("<script.*</script>"));
//    //html.remove(QRegularExpression("<script.*</script>", QRegularExpression::DotMatchesEverythingOption));
////    html.remove("BigPipe construction and first response"); ///<@todo ?
////    html.remove("&");
}
