#-------------------------------------------------
#
# Project created by QtCreator 2011-12-15T16:26:50
#
#-------------------------------------------------

QT       += core gui

TARGET = PDFSearch
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    listwidget.cpp \
    pdfview.cpp \
    pdfsearchlistwidgetitem.cpp

HEADERS  += mainwindow.h \
    listwidget.h \
    pdfview.h \
    pdfsearchlistwidgetitem.h

FORMS    += mainwindow.ui \
    pdfview.ui

LIBS += -lpoppler-qt4

TRANSLATIONS    = pdfsearch_en.ts \
                   pdfsearch_de.ts

