#ifndef CREATEGFM_H
#define CREATEGFM_H
#include "inc/parsers/parsergfm.h"
#include <QFile>
#include <QDataStream>
#include <QTextCodec>

class CreateGFM{
    QList<BlockGFM> *m_gfmBlocks;
    QFile *m_fileGFM;
    QTextCodec *m_usc_2_le_boom;
public:
    CreateGFM(QList<BlockGFM> *gfmBlocks);
    void create();
    ~CreateGFM();
};

#endif // CREATEGFM_H
