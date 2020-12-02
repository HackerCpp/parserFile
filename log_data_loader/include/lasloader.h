#ifndef LASLOADER_H
#define LASLOADER_H
#include "loader_global.h"
#include <aloaderlogdata.h>
#include <QHash>
#include <curve.h>
#include <datablock.h>

class LOADER_EXPORT LasLoader : public ALoaderLogData
{
    QTextCodec *m_codec;
    QString m_path;
    enum BlockLasType{V,W,C,P,O,A};
    struct BlockLas{
        BlockLasType typeBlockLas;
        QByteArray bodyBlockLas;
    };
    QHash<QString,BlockLasType> m_hashTypes;

    void findBlocks(const QByteArray &data,QList<BlockLas> *blocksLas);
    QString version(QList<BlockLas> *blocksLas);
    void parser20(const QList<BlockLas> &blocksLas);
    void findCurve(ICurve *curve,const QString &curveLine);
    void createCurves20(DataBlock *dataBlock,const QList<BlockLas> &blocksLas);
    void fillCurves20(DataBlock *dataBlock,const QList<BlockLas> &blocksLas);
    void findHeader20(const QList<BlockLas> &blocksLas);

public:
    LasLoader(QString path);
    ~LasLoader();

    bool download()override;
    void run()override;


};

#endif // LASLOADER_H
