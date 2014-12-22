#include "mainwindow.h"
#include <QApplication>
#include "browsertest.h"
#include <fstream>
#include <chtmlparser.hpp>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDate>
#include <QTextStream>
#include <QRegularExpression>
#include <list>
#include <QtTest/QTest>
#include <QDesktopServices>

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = msg;
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
        abort();
    }
    QFile outFile("D:\\log.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}
void makeAboutUrl(QString &url)
{
   if(url.toStdString().find("?id=") !=  std::string::npos)
   {
      url.append("&sk=about");
   } else
   {
      url.append("/about");
   }
}

QString makeWorkEducationUrl (QString url)
{
   if(url.toStdString().find("?id=") !=  std::string::npos)
   {
      return url.append("&section=education");
   } else
   {
      return url.append("?section=education");
   }
}
void loadUrlsFromFile(std::list<QString> &list)
{
    std::ifstream stream("D:\\facebook_urls.txt");
    std::string tmp;
    while(stream.good())
    {
       stream >> tmp;
       list.push_back(QString::fromStdString(tmp));
    }
}
void saveUrlsToFile(std::list<QString> &list)
{
    std::ofstream stream("D:\\saved_urls.txt");
    std::string tmp;
    for(auto it = list.begin(); it != list.end(); it++)
    {
        stream << (*it).toStdString() << std::endl;
    }
}

void stringToFile(QString text, QString fileName)
{
    std::ofstream of("D:\\" + fileName.toStdString() + ".html");
    of << text.toStdString();
    of.close();
}

//void byteToFile(QByteArray text, QString fileName)
//{
//   std::ofstream of("D:\\" + fileName.toStdString() + ".html");
//   for (auto it : text)
//   {
//      qDebug() << it;
//      of << text.toStdString();
//   }
//    of.close();
//}

void clearDublicates(std::list<QString> &list)
{
    for(auto it1 = list.begin(); it1 != list.end(); it1++)
    {
        auto it2 = it1;
        it2++;
        for(; it2 != list.end(); it2++)
        {
            if(*it1 == *it2)
            {
                list.erase(it2);
                it2--;
            }
        }
    }
}

int main(int argc, char *argv[])
{
   //qInstallMessageHandler(myMessageHandler);
   QDateTime mDateTimeStart(QDateTime::currentDateTime());

   QApplication a(argc, argv);

   BrowserTest b;
   CHTMLParser parser;

   qDebug() << QString("</script>").size();

   QString page = b.getPage(QUrl("http://www.deviantart.com/browse/all/?offset=50"));
   stringToFile(page, "MyOwnProject\\browse.all.html");
   std::deque <QPair<QString, QString>> deque;

   parser.parseImagesFromBrowsePage(page, deque);
   for (auto it : deque)
   {
      qDebug() << it.first;
      //qDebug() << it.second;
      //qDebug() << "";
   }
   b.getBytePage(QUrl(deque[0].first));
   //QDesktopServices::openUrl(QUrl(deque[2].second));

   QDateTime mDateTimeEnd(QDateTime::currentDateTime());
   int mTime = mDateTimeEnd.toTime_t() - mDateTimeStart.toTime_t();
   qDebug() << "Time: " << mTime;


   MainWindow w;
   w.setpixmap(QImage::fromData(b.getBytePage(QUrl(deque[4].second))), true);
   w.setpixmap(QImage::fromData(b.getBytePage(QUrl(deque[5].second))), false);
   w.showMaximized();


   return a.exec();
}
