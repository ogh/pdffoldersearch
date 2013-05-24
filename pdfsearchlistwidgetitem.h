#ifndef PDFSEARCHLISTWIDGETITEM_H
#define PDFSEARCHLISTWIDGETITEM_H

#include <QListWidgetItem>

class PDFSearchListWidgetItem : public QListWidgetItem
{
public:
    PDFSearchListWidgetItem(QString path, int page, QString name, QListWidget *parent);
    QString getPath()const{return path;}
    int getPage()const{return page;}
    QString getName()const{return name;}

private:
    QString path;
    int page;
    QString name;
};

#endif // PDFSEARCHLISTWIDGETITEM_H
