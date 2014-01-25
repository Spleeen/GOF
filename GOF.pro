#-------------------------------------------------
#
# Project created by QtCreator 2014-01-25T00:02:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GOF
TEMPLATE = app

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

SOURCES += main.cpp\
        mainwindow.cpp \
    Utilities.cpp \
    Grid.cpp \
    Cell.cpp

HEADERS  += mainwindow.h \
    Utilities.h \
    Grid.h \
    Cell.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    .DS_Store \
    .gitignore \
    Diagramme UML.gliffy \
    GOF.pro.user \
    Notes.txt
