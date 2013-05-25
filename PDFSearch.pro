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
win32{
    # Using a compiled version of libpoppler shipped with KDE for win
    LIBS += -L"C:\\Program Files\\KDE\\bin" -lpoppler-qt4
    INCLUDEPATH += "C:\\Program Files\\KDE\\include"
}
