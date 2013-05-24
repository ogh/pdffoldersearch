#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class ListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ListWidget(QString name, int page, QString path,QWidget *parent = 0);
    QString getPath();
    QString getName();
    int getPage();

private:
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QLabel *docName;
    QLabel *docPage;
    QLabel *docPath;
    QString name;
    int page;
    QString path;

signals:

public slots:

};

#endif // LISTWIDGET_H
