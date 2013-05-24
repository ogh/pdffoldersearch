#ifndef PDFVIEW_H
#define PDFVIEW_H

#include <QWidget>
#include <poppler/qt4/poppler-qt4.h>
#include <QResizeEvent>
#include <QLabel>

namespace Ui {
    class PDFview;
}

class PDFview : public QWidget
{
    Q_OBJECT

public:
    explicit PDFview(Poppler::Document *document,
                     int page,
                     QString readerPath,
                     QString documentPath,
                     QWidget *parent = 0);
    ~PDFview();
    void resizeEvent(QResizeEvent *event);

private:
    Ui::PDFview *ui;
    Poppler::Document *document;
    int page;
    int resizeDPI(Poppler::Page *page);
    void renderPDF();
    bool initialized;
    QLabel *lblPDF;
    int currentDPI;
    QString readerPath;
    QString documentPath;

public slots:
    void pageForward();
    void pageBack();
    void setToPage(int page);
private slots:
    void on_pushButton_clicked();
};

#endif // PDFVIEW_H
