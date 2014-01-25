#-------------------------------------------------
#
# Project created by QtCreator 2014-01-25T00:02:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GOF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cell.cpp \
    grid.cpp

HEADERS  += mainwindow.h \
    cell.h \
    grid.h \
    Utilities.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    .DS_Store \
    .gitignore \
    Diagramme UML.gliffy \
    GOF.pro.user \
    Notes.txt
