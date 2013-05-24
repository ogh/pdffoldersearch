#include "pdfsearchlistwidgetitem.h"
#include <QDebug>

PDFSearchListWidgetItem::PDFSearchListWidgetItem(QString path, int page,QString name, QListWidget *parent) :
    QListWidgetItem(parent),
    path(path),
    page(page),
    name(name)
{
}

//Dirty hack way to override the < operator of QListWidgetItem for custom sorting
bool QListWidgetItem::operator <(const QListWidgetItem &other)const
{
    if(const PDFSearchListWidgetItem *t = dynamic_cast<const PDFSearchListWidgetItem*>(this))
    {
        if(const PDFSearchListWidgetItem *o = dynamic_cast<const PDFSearchListWidgetItem*>(&other))
        {
            if(t->getName() == o->getName())
            {
                if(t->getPath() == o->getPath())
                {
                    if(t->getPage() == o->getPage())
                    {
                        //Equal
                        return false;
                    }
                    return t->getPage() < o->getPage();
                }
                return t->getPath() < o->getPath();
            }
            return t->getName() < o->getName();
        }
    }
    //If not PDFSearchListWidgetItem: do the usual comparison
    return this->text() < other.text();
}
