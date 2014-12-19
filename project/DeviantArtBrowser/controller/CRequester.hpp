#ifndef CREQUESTER_HPP
#define CREQUESTER_HPP

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

class CRequester : public QObject
{
   Q_OBJECT
public:
   explicit CRequester(QObject *parent = 0);

signals:

public slots:

};

#endif // CREQUESTER_HPP
