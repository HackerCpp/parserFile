#ifndef GFMLOADER_H
#define GFMLOADER_H

#include "loader_global.h"
#include <aloaderlogdata.h>
#include <QString>
#include <QThread>
#include <QTextCodec>
#include "headerblock.h"
#include "toolinfoblock.h"
#include "formsblock.h"
#include "datablock.h"
#include "unknownblock.h"
#include "curve.h"
#include "aboard.h"

class LOADER_EXPORT GFMLoader : public ALoaderLogData, public QThread{
    QString m_path;
    QTextCodec *m_codec;

    bool gzipCompress(QByteArray input, QByteArray &output, int level);
    bool gzipDecompress(QByteArray input, QByteArray &output);

public:
    GFMLoader(QString path);
    ~GFMLoader();

    bool download()override;
    void run()override;

    void parser(const QByteArray &bodyBlock,IBlock *block);
    void parserDataBlock(const QByteArray &bodyBlock,IBlock *block);
    void parserFormsBlock(const QByteArray &bodyBlock,IBlock *block);
    void parserToolInfoBlock(const QByteArray &bodyBlock,IBlock *block);
    void parserUnknownBlock(const QByteArray &bodyBlock,IBlock *block);
    void findShortCuts(QByteArray *header,DataBlock *dataBlock);
    void findCurves(QByteArray *header,DataBlock * dataBlock,QByteArray bodyBlock,int indexBeginData);
    void findCurveInfo(QByteArray curveLine,DataBlock *dataBlock,ICurve *curve,QByteArray bodyBlock,int indexBeginData);
    //void copyData(QByteArray bodyBlock,int indexBeginData,DataBlock * dataBlock);
    void parserHeaderBlock(const QByteArray &bodyBlock,IBlock *block);



};

#endif // GFMLOADER_H
