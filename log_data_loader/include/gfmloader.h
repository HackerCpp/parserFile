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
    void parserUnknownBlock(const QByteArray &bodyBlock,IBlock *block);
    void saveForm(FormsBlock * formsBlock);
    void findShortCuts(QByteArray *header,DataBlock *dataBlock);
    void findCurves(QByteArray *header,DataBlock * dataBlock);
    void findCurveInfo(QByteArray curveLine,DataBlock *dataBlock,ICurve *curve);
    void copyData(QByteArray bodyBlock,int indexBeginData,DataBlock * dataBlock);

};

#endif // GFMLOADER_H
