#ifndef GFMSAVER_H
#define GFMSAVER_H

#include "LogDataSaver_global.h"
#include <QThread>
#include "asaverlogdata.h"
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <shortcut.h>
#include <QtZlib/zlib.h>
#include <QXmlStreamReader>
#include "board.h"
#include "track.h"
#include "items.h"
#include "LineItem.h"
#include "markItem.h"
#include "AcuItem.h"
#include "formsblock.h"
#include <QTextCodec>
#include "datablock.h"

class SAVER_EXPORT GFMSaver: public ASaverLogData , QThread{
    QTextCodec *m_codec;
public:
    GFMSaver();
    ~GFMSaver()override;

    bool save()override;
    bool isReady()override;

    QByteArray formBlokSave(FormsBlock* formsBlock);
    //void saveBlock(QList<IBlock*> *m_blocks);
    bool gzipCompress(QByteArray input, QByteArray &output, int level);
    QByteArray  getForSave(IBlock *block);
    QByteArray  getForSaveDataBlock(IBlock *block);
    QByteArray  getForSaveFormsBlock(IBlock *block);
    QByteArray  getHeader(DataBlock*dataBlock);
    QByteArray  getForSaveHeaderBlock(IBlock *block);


};

#endif // GFMSAVER_H
