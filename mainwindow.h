#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QListWidgetItem>
#include <QProgressBar>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QDir *dir,QString readerPath, int maxHits=500, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnExecuteSearch_clicked();
    void showPDFView(QListWidgetItem  *item);

private:
    Ui::MainWindow *ui;
    QDir *dir;
    QFileInfoList *pdfs;
    QString readerPath;
    int maxHits;
    QProgressBar *pBar;
    int numPDFs;
    QString lastSearch;
    void addDocNPageToResultList(QString documentName, QFileInfo path, int page);
    bool searchPDFPostResults(const QFileInfo &filename, QString searchString);
};

#endif // MAINWINDOW_H
