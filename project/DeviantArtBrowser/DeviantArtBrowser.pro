#-------------------------------------------------
#
# Project created by QtCreator 2014-12-19T12:45:22
#
#-------------------------------------------------

QT       += core gui network webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeviantArtBrowser
TEMPLATE = app
CONFIG += c++11
CONFIG -= console

SOURCES += main.cpp\
        CView.cpp \
    CViewImage.cpp \
    controller/CController.cpp \
    controller/CRequester.cpp \
    controller/CDeviantArtParser.cpp \
    CFullSizeView.cpp

HEADERS  += CView.hpp \
    CViewImage.hpp \
    controller/CController.hpp \
    controller/CRequester.hpp \
    controller/CDeviantArtParser.hpp \
    controller/CMyCoolIterator.hpp \
    CFullSizeView.hpp

FORMS    += CView.ui
