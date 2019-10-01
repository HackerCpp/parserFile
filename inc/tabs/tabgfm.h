#ifndef TABGFM_H
#define TABGFM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <inc/parsers/parsergfm.h>
#include "inc/models/modelgfm.h"
#include <QGraphicsView>
#include "inc/tabs/graphicsview.h"

class TabGFM : public QWidget{
    Q_OBJECT

    ModelGFM * modelGfMScene;
    QWidget * sceneWidget;
    OGLGraphicsView * graphicsView;
    QHBoxLayout *mainHLayout;
    QScrollArea *scroll;
public:
    explicit TabGFM(FileReader *file,QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event);

signals:
    void tabGFMNewSize(QSize  size);


public slots:
};

#endif // TABGFM_H
