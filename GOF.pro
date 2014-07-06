#-------------------------------------------------
# Project created by QtCreator 2014-01-25T00:02:11
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GOF
TEMPLATE = app

QMAKE_CXXFLAGS += -O3 -pipe -fopenmp -std=c++11
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG  -march=native -fstack-protector --param=ssp-buffer-size=4

LIBS +=  -fopenmp -lpthread -D_REENTRANT


SOURCES += main.cpp\
        Mainwindow.cpp \
    Utilities.cpp \
    Grid.cpp \
    GOFScene.cpp

HEADERS  += Mainwindow.h \
    Utilities.h \
    Grid.h \
    GOFScene.h \
    Matrix.h

FORMS    += Mainwindow.ui

OTHER_FILES += \
    Diagramme UML.gliffy \
    Notes.txt \
    GOF.app
