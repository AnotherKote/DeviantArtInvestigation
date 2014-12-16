#ifndef CCOOKIE_HPP
#define CCOOKIE_HPP
#include <QNetworkCookieJar>
#include <QList>
#include <QNetworkCookie>
class CCookie : public QNetworkCookieJar
{
public:
   QList<QNetworkCookie> getCookies() const;
   CCookie();
};

#endif // CCOOKIE_HPP
