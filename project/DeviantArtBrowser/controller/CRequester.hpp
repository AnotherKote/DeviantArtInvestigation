#ifndef CREQUESTER_HPP
#define CREQUESTER_HPP

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QEventLoop>
#include <QUrl>
#include <QList>
#include "windows.h"

class CRequester : public QObject
{
   Q_OBJECT

   QNetworkAccessManager* mNetManager;
   QList<QNetworkAccessManager*> mNetMagagerList;

   QUrl mRedirectionURL;
   QEventLoop mLoadFinishedLoop;
   QByteArray mResultData;
   QList<QPair<QByteArray, QString>> mResultDataList;
   size_t mSync;

   CRITICAL_SECTION mCriticalSection;

   void redirect();
public:
   static bool autoRedirect;

   explicit CRequester(QObject *parent = 0);

   QByteArray get(QString url);
   QByteArray& post(QString url, QByteArray &data);
   QList<QPair<QByteArray, QString>> &getAsync(QList<QString> &urls);

   ~CRequester();
signals:

public slots:
   void finishedSlot(QNetworkReply *reply);
};

inline void CRequester::redirect()
{
   if(!mRedirectionURL.isEmpty())
   {
      mNetManager->get(QNetworkRequest(mRedirectionURL));
      mRedirectionURL.clear();
      mLoadFinishedLoop.exec();
   }
}

#endif // CREQUESTER_HPP
