#ifndef MODELTLM_H
#define MODELTLM_H

#include <QStandardItemModel>
#include "inc/parsers/parsertlm.h"

class ModelTlm{

    QList<BlockTlm> m_tlmBlocks;
    QStandardItemModel *model;
public:
    ModelTlm(QList<BlockTlm> &tlmBlocks);
    QStandardItemModel *getTlmModel();
};

#endif // MODELTLM_H
