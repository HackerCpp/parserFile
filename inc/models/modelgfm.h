#ifndef MODELGFM_H
#define MODELGFM_H

#include <QGraphicsScene>
#include <inc/parsers/parsergfm.h>


class ModelGFM : public QGraphicsScene{

public:
    ModelGFM(QList<BlockGFM> *gfmBlocks);
};

#endif // MODELGFM_H
