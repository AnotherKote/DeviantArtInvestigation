#ifndef CDEVIANTARTPARSER_HPP
#define CDEVIANTARTPARSER_HPP

#include <QList>
#include <QImage>
#include <QByteArray>
#include <model/CImageData.hpp>
#include <memory>

class CDeviantArtParser
{
public:
   CDeviantArtParser();

   bool parseImagesFromBrowsePage(QString &page, QList<std::shared_ptr<CImageData>> &images);
};

#endif // CDEVIANTARTPARSER_HPP
