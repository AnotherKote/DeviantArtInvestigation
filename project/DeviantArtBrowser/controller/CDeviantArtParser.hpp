#ifndef CDEVIANTARTPARSER_HPP
#define CDEVIANTARTPARSER_HPP

#include <QList>
#include <QImage>
#include <QByteArray>
#include <memory>
#include <QWidget>
#include "CViewImage.hpp"
#include "CView.hpp"

class CView;

class CDeviantArtParser
{
public:
   CDeviantArtParser();

   bool parseImagesFromBrowsePage(QString &page,
                                  QList<std::shared_ptr<CViewImage>> &images,
                                  const size_t count,
                                  CView *parent);
};

#endif // CDEVIANTARTPARSER_HPP
