#ifndef CIMAGE_HPP
#define CIMAGE_HPP

#include <QWidget>

class CImage : public QWidget
{
   Q_OBJECT
   QImage image;
   int id;
public:
   explicit CImage(QWidget *parent = 0);
   void setImage (QImage picture);
   int getId() const;
   void setId(int value);

signals:

public slots:


   // QWidget interface
protected:
   void paintEvent(QPaintEvent *);

   // QWidget interface
protected:
   void mousePressEvent(QMouseEvent *);
};

#endif // CIMAGE_HPP
