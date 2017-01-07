#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T21:23:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Vfp
TEMPLATE = app

QMAKE_CXXFLAGS = -std=c++11

SOURCES += main.cpp\
        View/mainview.cpp \
    View/setuptab.cpp \
    startup.cpp \
    utils.cpp \
    Model/settings.cpp

HEADERS  += View/mainview.h \
    View/setuptab.h \
    startup.h \
    utils.h \
    Model/settings.h

FORMS    += View/mainview.ui \
    View/setuptab.ui

RESOURCES += \
    vfpresources.qrc
