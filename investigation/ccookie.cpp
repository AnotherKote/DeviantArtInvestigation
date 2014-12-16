#include "ccookie.hpp"

QList<QNetworkCookie> CCookie::getCookies() const
{
   return allCookies();
}

CCookie::CCookie()
{
}
