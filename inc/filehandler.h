#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QWidget>
#include "inc/models/model38k.h"
#include <QList>

class FileHandler : public QWidget{

    Q_OBJECT
    QList<QWidget*> *widgets;
public:
    FileHandler(QWidget *parent = nullptr);
    QWidget *getWidget(QString path);
};

#endif // FILEHANDLER_H
