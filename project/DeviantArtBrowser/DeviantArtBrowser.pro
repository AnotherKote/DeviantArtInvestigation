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

SOURCES += main.cpp\
        CView.cpp \
    CViewImage.cpp \
    controller/CController.cpp \
    controller/CRequester.cpp \
    controller/CDeviantArtParser.cpp \
#    model/CModel.cpp \
#    model/CViewImage.cpp

HEADERS  += CView.hpp \
    CViewImage.hpp \
    controller/CController.hpp \
    controller/CRequester.hpp \
    controller/CDeviantArtParser.hpp \
#    model/CModel.hpp \
#    model/CViewImage.hpp

FORMS    += CView.ui
