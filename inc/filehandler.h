#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QTableView>
#include "inc/models/model38k.h"

class FileHandler : public QWidget{

    Q_OBJECT

    QWidget *widget;
    QHBoxLayout *horBoxLayout;
    QTableView *table;
    QPlainTextEdit *textEdit;
    Model38k *model;
public:
    FileHandler(QString path,QWidget *parent = nullptr);
    QWidget *getWidget(){return widget;}
public slots:
    void showText(QModelIndex const& index);
};

#endif // FILEHANDLER_H
