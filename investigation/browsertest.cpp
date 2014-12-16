#include "browsertest.h"
#include <fstream>
#include <iostream>
#include <QDebug>
#include <QEventLoop>
#include <QtTest/QTest>
#include <QObject>
#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkDiskCache>
#include <QNetworkCookieJar>
#include <QDebug>
#include <QString>
//#include <QImageReader>
//#include <QScriptEngine>
//#include <QScriptValue>
//#include <QScriptValueIterator>
#include <QNetworkProxy>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QUrlQuery>

using namespace std;

void BrowserTest::redirect()
{
   if(!mRedirectionURL.isEmpty())
   {
      mNetManager->get(QNetworkRequest(mRedirectionURL));
      mRedirectionURL.clear();
      mNetworkReplyFinishedLoop.exec();
   }
}

QString &BrowserTest::getPage(QUrl url)
{
   qDebug() << "Getting page " << url;
   QNetworkRequest req(url);
   //req.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.3; Trident/7.0; rv:11.0) like Gecko");
   mNetManager->get(req);
   mNetworkReplyFinishedLoop.exec();
   //QTest::qSleep(10000);
   redirect();

   return mResultHtml;
}

QByteArray &BrowserTest::getBytePage(QUrl url)
{
   qDebug() << "Getting page " << url;
   QNetworkRequest req(url);
   //req.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.3; Trident/7.0; rv:11.0) like Gecko");
   mNetManager->get(req);
   mNetworkReplyFinishedLoop.exec();
   //QTest::qSleep(10000);
   redirect();

   return mResultByteArray;
}

QString &BrowserTest::post(QUrl url, QByteArray data)
{
   qDebug() << "Posting page " << url;
   QNetworkRequest req(url);
   //req.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.3; Trident/7.0; rv:11.0) like Gecko");
   req.setHeader(QNetworkRequest::ContentTypeHeader,
       "application/x-www-form-urlencoded");
//   req.setRawHeader("Accept-Language", "uk-UA,uk;q=0.8,ru;q=0.6,en-US;q=0.4,en;q=0.2");
//   req.setRawHeader("Referer", "https://www.facebook.com/search/results/?q=ivan&type=users");
//   req.setRawHeader("Origin", "https://www.facebook.com");
   mNetManager->post(req, data);
   mNetworkReplyFinishedLoop.exec();
   redirect();
   return mResultHtml;
}

QString &BrowserTest::authorization(QString login, QString password,
                                   QString loginFieldName,
                                   QString passwordFieldName, QUrl loginURL)
{
   qDebug() << "Authorization...";

   QUrlQuery some;
   some.addQueryItem(loginFieldName, login);
   some.addQueryItem(passwordFieldName, password);

   QNetworkRequest request(loginURL);
   request.setHeader(QNetworkRequest::ContentTypeHeader,
       "application/x-www-form-urlencoded");
   mNetManager->post(request, some.toString(QUrl::FullyEncoded).toUtf8());
   mNetworkReplyFinishedLoop.exec();
   redirect();
   return mResultHtml;
}

QList<QNetworkCookie> BrowserTest::getCookieForURL()
{
   return mCookieJar.getCookies();
}

BrowserTest::BrowserTest()
   :mNetManager(new QNetworkAccessManager),
    mRedirectionURL("")
{
   mNetManager->setCookieJar(&mCookieJar);
   QNetworkProxy proxy;
   proxy.setType(QNetworkProxy::HttpProxy);
   proxy.setHostName("localhost");
   proxy.setPort(8888);
//   QNetworkProxy::setApplicationProxy(proxy);
   mNetManager->setProxy(proxy);
   QObject::connect(mNetManager, SIGNAL(finished(QNetworkReply*)),&mNetworkReplyFinishedLoop, SLOT(quit()));
   QObject::connect(mNetManager, &QNetworkAccessManager::finished, this, &BrowserTest::finishedSlot);
}

BrowserTest::~BrowserTest()
{
   qDebug() << "DELETED!";
}


void BrowserTest::finishedSlot(QNetworkReply *reply)
{
    // Reading attributes of the reply
    // e.g. the HTTP status code
    QVariant statusCodeV =
    reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    // Or the target URL if it was a redirect:
    QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(!redirectionTargetUrl.toString().isEmpty())
    {
       mRedirectionURL = redirectionTargetUrl.toUrl();
       qDebug() << "redirecting to " << mRedirectionURL;
       delete reply;
       return;
    }
//    qDebug () << " HAAS HEADER : " <<  reply->hasRawHeader(QString("X-LI-UUID").toUtf8());
//    qDebug () << " header value: " << reply->rawHeader(QString("X-LI-UUID").toUtf8());
    if(reply->error() == QNetworkReply::NoError)
    {
       mResultByteArray = reply->readAll();  // bytes
       QString string(mResultByteArray);
       mResultHtml = string;
       //qDebug() << string;

       //ofstream out;
       //out.open("D://index.html");
       //out << string.toStdString();
       //qDebug() << reply->url().toString();
    }
    else
    {
       qDebug() << "error :";
       qDebug() << reply->url();
       qDebug() << reply->errorString();
       qDebug() << reply->error();
        // handle errors here
    }
    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    delete reply;
}


