#ifndef DATABLOCK_H
#define DATABLOCK_H

#include "ablock.h"
#include "icurve.h"

class DataBlock : public ABlock{
    QList<ICurve> *m_curves;

public:
    DataBlock();
    ~DataBlock();

};

#endif // DATABLOCK_H
