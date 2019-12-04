#ifndef ParserGFM_H
#define ParserGFM_H

#include "QString"
#include "QList"
#include "inc/parsers/findblocks.h"
#include "inc/filereader.h"

#pragma pack(push,1)
struct HeaderData{
    QByteArray dataString;
};
struct ToolInfoData{
    QByteArray dataString;
};
struct DataBlockCurve{
    uint offset;
    uint size;
    uint sizeofType;
    QString parameterMnemonics;
    QString dataType;
    QString recordPoint;
    QByteArray desc;
    QVector<qreal> *data;
};
struct UnknownData{
    QByteArray dataString;
};
struct BlockGFMData{
    int type;
};
struct HeaderBlock : public BlockGFMData{
    QList<HeaderData> data;
};
struct ToolInfoBlock : public BlockGFMData{
    QList<ToolInfoData> data;
};
struct DataBlock : public BlockGFMData{
    uint numberOfVectors;
    QString nameRecord;
    QString moduleMnemonics;
    QString plugins;
    QList<DataBlockCurve> *curves;
};
struct UnknownBlock : public BlockGFMData{
    QList<UnknownData> data;
};
struct BlockGFM{
    QString boom;
    QString name;
    BlockGFMData *data;
};
#pragma pack(pop)

class ParserGFM{

    QList<BlockGFM> *m_gfmBlocks;
public:

    ParserGFM(FileReader *file);
    void parserHeaderBlock(QByteArray *bodyBlock,BlockGFM *block);
    void parserToolInfoBlock(QByteArray *bodyBlock,BlockGFM *block);
    void parserDataBlock(QByteArray *bodyBlock,BlockGFM *block);
    void parserUnknownBlock(QByteArray *bodyBlock,BlockGFM *block);
    QList<BlockGFM> *getGFMBlocks();
    ~ParserGFM();
};

#endif // ParserGFM_H
