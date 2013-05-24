#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <poppler/qt4/poppler-qt4.h>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>
#include <listwidget.h>
#include <QPushButton>
#include "pdfview.h"
#include "pdfsearchlistwidgetitem.h"
#include <QStatusBar>

#define MAXDEPTH 30

QFileInfoList* scanForPDFs(QDir *dir, QFileInfoList *pdfs = 0, int depth=0)
{
    if(pdfs == NULL)
        pdfs = new QFileInfoList();
    QFileInfoList fl = dir->entryInfoList();
    //run over all items in directory "dir"
    QFileInfo currFI;
    for(int i = 0; i < fl.size(); i++)
    {
        currFI = fl.at(i);
        //Don't follow links
        if (currFI.isSymLink())
            continue;
        if(currFI.isFile() && currFI.suffix().toLower() == "pdf")
        {
            //If current object is file and .pdf
            //=> add it to the result list
            pdfs->append(currFI);
        }else if(currFI.isDir())
        {
            //Check whether at MAXDEPTH
            if(depth >= MAXDEPTH)
            {
                QMessageBox mbox;
                mbox.setText(QMessageBox::tr("Reached max search depth"));
                continue;
            }
            //we don't wanna run into a circle
            if(currFI.fileName() == "." || currFI.fileName() == "..")
                continue;
            //If current object is a directory
            // => call this function recursively
            QDir *cDir = new QDir(currFI.absoluteFilePath());
            scanForPDFs(cDir, pdfs, depth+1);
            delete cDir;
        }
    }
    //Directory was searched recursively for PDF files
    //=> return resulting list if PDF file names
    return pdfs;
}

MainWindow::MainWindow(QDir *dir, QString readerPath, int maxHits, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dir(dir),
    readerPath(readerPath),
    lastSearch(QString("")),
    maxHits(maxHits)
{
    //scan for pdfs in the given searchfolder
    pdfs = new QFileInfoList();
    scanForPDFs(dir,pdfs);
    numPDFs = pdfs->size();
    //If no PDFs found => terminate application
    if(numPDFs == 0)
    {
        QMessageBox mbox;
        mbox.setText(tr("No pdfs found"));
        mbox.exec();
        QApplication::exit(0);
    }
    //Setup UI
    ui->setupUi(this);
    connect(ui->lstResults,SIGNAL(itemActivated(QListWidgetItem*))
            ,this,SLOT(showPDFView(QListWidgetItem*)));
    //Add progressbar to statusbar
    pBar = new QProgressBar(this);
    pBar->setVisible(false);
    pBar->setMinimum(0);
    pBar->setMaximum(numPDFs);
    ui->statusBar->addPermanentWidget(pBar);
}

MainWindow::~MainWindow()
{
    delete pdfs;
    delete ui;
}

/**
 * @brief MainWindow::addDocNPageToResultList
 * @param documentName Name of the pdf document that will be displayed in the list
 * @param fi file info object for the pdf file
 * @param page page of the search term match
 *
 *  Adds a given document/page match to the list of matches
 */
void MainWindow::addDocNPageToResultList(QString documentName, QFileInfo fi, int page)
{
    PDFSearchListWidgetItem *item =
            new PDFSearchListWidgetItem(fi.absoluteFilePath(), page, documentName,ui->lstResults);
    item->setSizeHint(QSize(80,80));
    ListWidget *lw = new ListWidget(documentName,page, fi.absoluteFilePath());
    ui->lstResults->setItemWidget(item,lw);
}

//TODO think about storing the documents instead of the filenames in a list
//Would avoid creation of the documents for each search but probably take up more memory
bool MainWindow::searchPDFPostResults(const QFileInfo &fi, QString searchString)
{
    bool nHitsExceeded = false;
    Poppler::Document *document = Poppler::Document::load(fi.absoluteFilePath());
    if (!document || document->isLocked()) {
      //Oops, document empty => error message
      QMessageBox mbox;
      mbox.setText(tr("Could not read the file \n'") + fi.fileName() +
                   tr("\ntherefore, possible matches might be missing"));
      mbox.exec();
      delete document;
      return false;
    }
    //Get document title
    QString title = document->info("Title");
    //If no title specified => use filename instead
    if(title == "")
        title = fi.fileName();
    QString shortTitle = QString(title);
    if (shortTitle.length() > 16)
    {
        shortTitle = "..." + shortTitle.right(16);
    }
    ui->statusBar->showMessage("Durchsuche PDF: " + shortTitle);
    qDebug() << "Searching pdf: " << title;
    //Search the document for the searchString
    int hitCounter = 0;
    for (int page = 0; page < document->numPages(); page++) {
        //Parameters 1,2,3,4 of the search function
        //will contain the rectangle coordinates of where the text was found.
        //Since we are not interested in these coordinates, we just pass a single variable
        double coordinate = 0.0;
        if (document->page(page)->search(searchString, coordinate,coordinate,coordinate,coordinate,
            Poppler::Page::NextResult,
            Poppler::Page::CaseInsensitive)) {
            hitCounter++;
            ui->statusBar->showMessage(tr("Searching in ") + shortTitle +
                                       " - hit on page: " + QString::number(page));
            //Yay, we found the search String on this page
            //=> Add this page to the result list
            addDocNPageToResultList(title, fi, page);
            // TODO make this limit a variable
            if(hitCounter >= maxHits)
            {
                QMessageBox mbox;
                mbox.setText(tr("Search has already reached the maximum of ") + QString::number(maxHits)
                             + tr(" please choose a more specific criterion"));
                mbox.exec();
                nHitsExceeded = true;
                break;
            }
        }
    }

    //Don't forget to delete the document
    delete document;
    //Return whether the max number of hits was reached
    return nHitsExceeded;
}

void MainWindow::on_btnExecuteSearch_clicked()
{
    //Don't do the same search again
    if (lastSearch == ui->txtSearchTerm->text())
    {
        return;
    }
    if(ui->txtSearchTerm->text() == "")
    {
        QMessageBox mbox;
        mbox.setText(tr("Please specify a search term"));
        mbox.exec();
        return;
    }
    lastSearch = ui->txtSearchTerm->text();
    //Clear result list
    ui->lstResults->clear();
    //Disable button and show status and progressbar
    ui->btnExecuteSearch->setDisabled(true);
    ui->btnExecuteSearch->setEnabled(false);
    pBar->setValue(0);
    pBar->setVisible(true);
    ui->statusBar->showMessage(tr("searching ..."));
    for(int i = 0; i < numPDFs; i++)
    {
        if(searchPDFPostResults(pdfs->at(i),ui->txtSearchTerm->text()))
        {
            break;
        }
        pBar->setValue(i);
    }
    //Enable button and hide status progressbar
    ui->btnExecuteSearch->setDisabled(false);
    ui->btnExecuteSearch->setEnabled(true);
    ui->statusBar->showMessage(tr("Finished search"));
    pBar->setVisible(false);
}

void MainWindow::showPDFView(QListWidgetItem *item)
{
    ListWidget *w = (ListWidget*)(ui->lstResults->itemWidget(item));
    Poppler::Document *document = Poppler::Document::load(w->getPath());
    PDFview *view = new PDFview(document,w->getPage(), readerPath, w->getPath());
    view->setAttribute(Qt::WA_DeleteOnClose);
    view->setWindowTitle("PDF Folder Search");
    view->showMaximized();
}

