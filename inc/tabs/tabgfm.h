#ifndef TABGFM_H
#define TABGFM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <inc/parsers/parsergfm.h>
#include "inc/models/modelgfm.h"
#include <QGraphicsView>

class TabGFM : public QWidget{
    Q_OBJECT

    ModelGFM * modelGfMScene;
    QWidget * sceneWidget;
    QGraphicsView * graphicsView;
    QHBoxLayout *mainHLayout;
    QScrollArea *scroll;
public:
    explicit TabGFM(FileReader *file,QWidget *parent = nullptr);

signals:

public slots:
};

#endif // TABGFM_H
