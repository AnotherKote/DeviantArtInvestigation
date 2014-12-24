#ifndef CDEVIANTARTPARSER_HPP
#define CDEVIANTARTPARSER_HPP

#include <QList>
#include <QImage>
#include <QByteArray>
#include <memory>
#include <QWidget>
#include "CViewImage.hpp"


class CDeviantArtParser
{
public:
   CDeviantArtParser();

   bool parseImagesFromBrowsePage(QString &page,
                                  QList<std::shared_ptr<CViewImage>> &images,
                                  const size_t count);
};

#endif // CDEVIANTARTPARSER_HPP
