#include "pdfview.h"
#include "ui_pdfview.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileInfo>
#include <QProcess>


PDFview::PDFview(Poppler::Document *document,
                 int page,QString readerPath,
                 QString documentPath,
                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PDFview),
    document(document),
    page(page),
    currentDPI(72),
    readerPath(readerPath),
    documentPath(documentPath)
{
    initialized = false;
    ui->setupUi(this);
    //There seems to be a bug when using a layout within the scollarea
    //that was created by in the designer
    //The width of the label in this layout does not seem to be updated
    //Workaround: create the layout and the label ourselves
    lblPDF = new QLabel("");
    lblPDF->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    layout->addWidget(lblPDF);
    //Render first page
        //Set render hint for antialiasing
    document->setRenderHint(Poppler::Document::TextAntialiasing);
        //Render the actual PDF
    int dpi = resizeDPI(document->page(page));
    qDebug() << "Resizing done";
    QImage image = document->page(page)->renderToImage(
                dpi,dpi);
    lblPDF->setPixmap(QPixmap::fromImage(image));
    initialized = true;
}

PDFview::~PDFview()
{
    delete ui;
}

int PDFview::resizeDPI(Poppler::Page *page)
{
    float numerator = (float)(lblPDF->width()); //How many dots
    float denominator = (float)(page->pageSize().width()/72.f); //How many inches
    int dpi = (int)((numerator/denominator)); //Number of dots / number of inches
    //Update the global DPI value
    currentDPI = dpi;
    return dpi;
}

void PDFview::resizeEvent(QResizeEvent *event)
{
    if(!initialized)
        return;
    int dpi = resizeDPI(document->page(page));
    QImage image = document->page(page)->renderToImage(
                dpi,dpi);
    lblPDF->setPixmap(QPixmap::fromImage(image));
}

void PDFview::pageForward()
{
    if(page + 1 < document->numPages())
        page++;
    QImage image = document->page(page)->renderToImage(
                currentDPI,currentDPI);
    lblPDF->setPixmap(QPixmap::fromImage(image));
}

void PDFview::pageBack()
{
    qDebug() << page;
    if(page - 1 >= 0)
        page--;
    QImage image = document->page(page)->renderToImage(
                currentDPI,currentDPI);
    lblPDF->setPixmap(QPixmap::fromImage(image));
}

void PDFview::setToPage(int page)
{
    if(page >= 0 && page < document->numPages())
        this->page = page;
    QImage image = document->page(page)->renderToImage(
                currentDPI,currentDPI);
    lblPDF->setPixmap(QPixmap::fromImage(image));
}



void PDFview::on_pushButton_clicked()
{
    //Check whether a path to adobe reader was specified
    if(readerPath == NULL)
    {
        QMessageBox mbox;
        mbox.setText(tr("Path to Adobe Reader not specified"));
        mbox.exec();
        return;
    }
    //Check whether the specified file exists
    QFileInfo fi = QFileInfo(readerPath);
    if(!fi.exists())
    {
        QMessageBox mbox;
        mbox.setText(tr("Specified path to Adobe Reader does not exist"));
        mbox.exec();
        return;
    }

    QProcess process(this);
    bool started = process.startDetached("\"" + readerPath + "\" " +
                                         + "\"" + documentPath + "\"");
    if(!started)
    {
        QMessageBox mbox;
        mbox.setText(tr("Starting Adobe Reader failed"));
        mbox.exec();
        return;
    }


}
