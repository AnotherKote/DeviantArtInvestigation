#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <imageviewer.hpp>
#include <QLabel>
#include <QScrollArea>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

   static size_t count;

   imageViewer *mainWidget;
   QLabel *mImageLabel;
   QLabel *mImageTip;
   QScrollArea *mScrollArea;
   QImage mPixmap;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setpixmap(QImage pixmap);
private:
    Ui::MainWindow *ui;

private slots:
    void centralWidgetPaintSlot(QPaintEvent *);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
