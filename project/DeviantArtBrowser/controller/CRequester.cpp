#include "CRequester.hpp"
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkReply>
#include <QDebug>

using namespace NWindowsGarbage;

bool CRequester::autoRedirect = true;

CRequester::CRequester(QObject *parent)
   : QObject(parent),
     mNetManager(new QNetworkAccessManager),
     mRedirectionURL(""),
     mSync(0)
{
   InitializeCriticalSection(&mCriticalSection);

   QNetworkProxy proxy;
   proxy.setType(QNetworkProxy::HttpProxy);
   proxy.setHostName("localhost");
   proxy.setPort(8888);
//   QNetworkProxy::setApplicationProxy(proxy);
   mNetManager->setProxy(proxy);
   QObject::connect(mNetManager, SIGNAL(finished(QNetworkReply*)),&mLoadFinishedLoop, SLOT(quit()));
   QObject::connect(mNetManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
}

QByteArray CRequester::get(QString url)
{
   EnterCriticalSection(&mCriticalSection);
   mResultDataList.clear();
   qDebug() << "Getting " << url;

   QNetworkRequest req(url);
   mNetManager->get(req);
   mLoadFinishedLoop.exec();

   redirect();
   LeaveCriticalSection(&mCriticalSection);
   return ((*mResultDataList.begin()).first);
}

QByteArray& CRequester::post(QString url, QByteArray &data)
{
   mResultDataList.clear();

   qDebug() << "Posting URL: " << url;
   qDebug() << "Data: " << QString::number(data.size()) << "bytes.";

   QNetworkRequest req(url);
   req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
   mNetManager->post(req, data);
   mLoadFinishedLoop.exec();

   redirect();
   if(mResultDataList.empty())
   {
      return mResultData;
   }
   else
   {
      return ((*mResultDataList.begin()).first);
   }
}

QList<QPair<QByteArray,QString>>& CRequester::getAsync(QList<QString> &urls)
{
   EnterCriticalSection(&mCriticalSection);
   mResultDataList.clear();
   mSync = urls.size();
   for (auto url: urls)
   {
      mNetManager->get(QNetworkRequest(url));
   }
   for(int i = 0; i < urls.size(); i++)
   {
      if(mSync > 0)
      {
         mLoadFinishedLoop.exec();
      }
   }
   return mResultDataList;
   LeaveCriticalSection(&mCriticalSection);
}

CRequester::~CRequester()
{
   delete mNetManager;
   DeleteCriticalSection(&mCriticalSection);
}

void CRequester::finishedSlot(QNetworkReply *reply)
{
   EnterCriticalSection(&mCriticalSection);
   mSync--;
   qDebug() << "finished loop " << mSync;
   QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
   if(!redirectionTargetUrl.toString().isEmpty())
   {
      mRedirectionURL = redirectionTargetUrl.toUrl();
      qDebug() << "redirecting to " << mRedirectionURL;
      delete reply;
      return;
   }

   if(reply->error() == QNetworkReply::NoError)
   {
      mResultDataList.append(QPair<QByteArray, QString>(reply->readAll(), reply->url().toString()));  // bytes
   }

   else
   {
      ///<@todo on error append default picture and name;
      qDebug() << "error :";
      qDebug() << reply->url();
      qDebug() << reply->errorString();
      qDebug() << reply->error();
   }

   delete reply;

   LeaveCriticalSection(&mCriticalSection);
}
