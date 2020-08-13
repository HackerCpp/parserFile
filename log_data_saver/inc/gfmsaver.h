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
#include "lineItem.h"
#include "markItem.h"
#include "acuItem.h"
#include "formsblock.h"
#include <QTextCodec>
#include "datablock.h"

class SAVER_EXPORT GFMSaver: public ASaverLogData {
    QTextCodec *m_codec;
public:
    GFMSaver();
    ~GFMSaver()override;

    bool save()override;
    bool isReady()override;

    QByteArray formBlokSave(FormsBlock* formsBlock);
    bool gzipCompress(QByteArray input, QByteArray &output, int level);
    QByteArray  getForSave(IBlock *block);
    QByteArray  getForSaveDataBlock(IBlock *block);
    QByteArray  getForSaveFormsBlock(IBlock *block);
    QByteArray  getHeader(DataBlock*dataBlock);
    QByteArray  getDesc(Desc *desc);
    QByteArray  getForSaveHeaderBlock(IBlock *block);
    QByteArray  getForSaveToolInfoBlock(IBlock *block);
};

#endif // GFMSAVER_H
