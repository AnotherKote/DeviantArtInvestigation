#ifndef CDEVIANTARTPARSER_HPP
#define CDEVIANTARTPARSER_HPP

#include <QList>
#include <QImage>
#include <QByteArray>

class CDeviantArtParser
{
public:
   CDeviantArtParser();
   bool parseImages (QList<QImage>& resultImages, QByteArray& page);
};

#endif // CDEVIANTARTPARSER_HPP
