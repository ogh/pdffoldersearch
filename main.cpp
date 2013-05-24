#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Check whether number of arguments equals 2 (1: Programname; 2: searchpath)
        //If yes => fine
        //If no => output message, end program

    QString searchPath;
    QString readerPath = NULL;
    int maxHits = 500;
    // TODO use a proper argument parser
    if(a.arguments().size() == 2)
    {
        searchPath = a.arguments().at(1);
    }
    else if(a.arguments().size() == 3)
    {
        searchPath = a.arguments().at(1);
        readerPath = a.arguments().at(2);
    }
    else if(a.arguments().size() == 4)
    {
        searchPath = a.arguments().at(1);
        readerPath = a.arguments().at(2);
        maxHits = a.arguments().at(3).toInt();
    }
    else
    {
        QMessageBox mbox;
        mbox.setText(QApplication::tr("Please declare a search path"));
        mbox.exec();
        return EXIT_FAILURE;
    }

    //Create the QDir Object
    QDir *dir = new QDir(a.arguments().at(1));
    //Check whether the directory actually exists
    if(!dir->exists())
    {
        //If directory does not exist => show message and exit
        QMessageBox msgbox;
        msgbox.setText(QApplication::tr("Searchpath does not exist"));
        msgbox.exec();
        return EXIT_FAILURE;
    }

    //if everything has been fine to this point => create the main window
    MainWindow w(dir, readerPath, maxHits);
    w.setWindowTitle(QApplication::tr("Searching ..."));
    w.show();

    return a.exec();
}
