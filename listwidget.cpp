#include "listwidget.h"
#include <QFont>

// TODO using a listwidget is not the best idea for this since we have
// to update the list constantly while searching the PDFs
// and we always want to keep it sorted
// There are better alternatives for this job

ListWidget::ListWidget(QString name, int page, QString path,QWidget *parent) :
    QWidget(parent),
    name(name),page(page),path(path)
{
    hLayout = new QHBoxLayout();
    vLayout = new QVBoxLayout(this);

    docName = new QLabel(name);
    QString docStyleSheet = "QLabel { background-color : rgba(8,90,0, 255);";
    docStyleSheet +=  "color : white; border-radius: 10px;}";
    QFont docNameFont = QFont(docName->font());
    docNameFont.setBold(true);
    docNameFont.setPointSize(14);
    docName->setFont(docNameFont);
    docName->setStyleSheet(docStyleSheet);
    docName->setAlignment(Qt::AlignCenter);
    docPage = new QLabel(tr("Page ") + QString::number(page+1));
    QFont docPageFont = QFont(docPage->font());
    docPageFont.setBold(true);
    docPageFont.setPointSize(12);
    docPage->setFont(docPageFont);
    docPage->setAlignment(Qt::AlignCenter);
    docPath = new QLabel(path);

    hLayout->addWidget(docName);
    hLayout->addWidget(docPage);

    this->setMinimumHeight(80);

    vLayout->addLayout(hLayout);
    vLayout->addWidget(docPath);
}

QString ListWidget::getPath()
{
    return this->path;
}

QString ListWidget::getName()
{
    return this->name;
}

int ListWidget::getPage()
{
    return page;
}
