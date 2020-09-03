#ifndef LASLOADER_H
#define LASLOADER_H
#include "loader_global.h"
#include <aloaderlogdata.h>
#include <QThread>
#include <QHash>

class LOADER_EXPORT LasLoader : public ALoaderLogData, public QThread
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
    void parser20(QList<BlockLas> *blocksLas);
    void createCurves20(QList<BlockLas> *blocksLas);

public:
    LasLoader(QString path);
    ~LasLoader();

    bool download()override;
    void run()override;


};

#endif // LASLOADER_H
