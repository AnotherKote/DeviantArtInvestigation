#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <imageviewer.hpp>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <CImage.hpp>
#include <QList>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
   CImage *imageObject, *imageObject2;
   static size_t count;
   QPushButton *button;
   imageViewer *mainWidget;
   QLabel *mImageLabel;
   QLabel *mImageTip;
   QScrollArea *mScrollArea;
   QList<QImage> mPixmapList;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setpixmap(QImage pixmap, bool first);
private:
    Ui::MainWindow *ui;

signals:
    void showFullSize(int id);

private slots:
    void centralWidgetPaintSlot(QPaintEvent *);
    void buttonPressed();
    void buttonPressedInt (int id);
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
