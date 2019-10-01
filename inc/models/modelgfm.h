#ifndef MODELGFM_H
#define MODELGFM_H

#include <QGraphicsScene>
#include <inc/parsers/parsergfm.h>
#include <QObject>


class ModelGFM : public QGraphicsScene{
    Q_OBJECT

public:
    ModelGFM(QList<BlockGFM> *gfmBlocks);
    void connectView();
signals:
    void scrollChange(qreal leftX,qreal topY,qreal rightX,qreal downY);

};

#endif // MODELGFM_H
