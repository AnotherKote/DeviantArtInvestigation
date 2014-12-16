#ifndef CHTMLPARSER_HPP
#define CHTMLPARSER_HPP

#include <QXmlStreamReader>
#include <deque>

class CHTMLParser
{
protected:
   void errorMessenger(QXmlStreamReader &stream);

public:
   CHTMLParser();
   bool parseImagesFromBrowsePage(QString &page, std::deque<QPair<QString, QString> > &queue);
   static void removeScriptAndComment(QString &html);
   static void removeBetweenIncluding(QString &text, QString start_text, QString end_text);
   static void getBetweenIncluding (QString &text, QString left_text, QString right_text);
};

#endif // CHTMLPARSER_HPP
