#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T11:33:05
#
#-------------------------------------------------

QT       += core gui testlib script network webkitwidgets
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebBrowserTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        browsertest.cpp \
        chtmlparser.cpp \
    ccookie.cpp \
    imageviewer.cpp \
    CImage.cpp

HEADERS  += mainwindow.h \
            browsertest.h \
            chtmlparser.hpp \
    ccookie.hpp \
    imageviewer.hpp \
    CImage.hpp

FORMS    += mainwindow.ui
