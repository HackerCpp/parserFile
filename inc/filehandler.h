#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QWidget>
#include "inc/models/model38k.h"


class FileHandler : public QWidget{

    Q_OBJECT

public:
    FileHandler(QWidget *parent = nullptr);
    QWidget *getWidget(QString path);
};

#endif // FILEHANDLER_H
