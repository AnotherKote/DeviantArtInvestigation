#ifndef BROWSERTEST_H
#define BROWSERTEST_H
#include<QObject>
#include<list>
#include<QEventLoop>
#include<QtNetwork>
#include<ccookie.hpp>

class BrowserTest : public QObject
{
private:
    QString mResultHtml;
    QByteArray mResultByteArray;
    CCookie mCookieJar;
//    std::list<QString> mListOfUrls;
    QUrl mRedirectionURL;
    QNetworkAccessManager *mNetManager;
    QEventLoop mNetworkReplyFinishedLoop;

    void makeFromPageUrlAboutUrl();
public:
    BrowserTest();
    ~BrowserTest();
    void redirect();
    QString &getPage(QUrl url);
    QByteArray &getBytePage(QUrl url);
    QString &post(QUrl url, QByteArray data);
    QString &authorization(QString login, QString password,
                          QString loginFieldName, QString passwordFieldName,
                          QUrl loginURL);
    QList<QNetworkCookie> getCookieForURL ();

signals:
public slots:
  void finishedSlot(QNetworkReply*reply);
};

#endif // BROWSERTEST_H
