#ifndef CFULLSIZEVIEW_HPP
#define CFULLSIZEVIEW_HPP

#include <QDialog>
#include <QImage>
#include <QLabel>

class CFullSizeView : public QDialog
{
   Q_OBJECT
   QLabel* mImage;
public:
   explicit CFullSizeView(QImage image, QWidget *parent = 0);

signals:

public slots:

//protected:
//   void paintEvent(QPaintEvent *);
};

#endif // CFULLSIZEVIEW_HPP
