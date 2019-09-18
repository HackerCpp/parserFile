#ifndef ParserGFM_H
#define ParserGFM_H

#include "QString"
#include "QList"
#include "inc/parsers/findblocks.h"
#include "inc/filereader.h"

struct HeaderData{
    QByteArray dataString;
};
struct ToolInfoData{
    QByteArray dataString;
};
struct DataBlockData{
    QByteArray header;
    QByteArray data;
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
    DataBlockData data;
};
struct UnknownBlock : public BlockGFMData{
    QList<UnknownData> data;
};
struct BlockGFM{
    QString boom;
    QString name;
    BlockGFMData *data;
};


class ParserGFM{

    QList<BlockGFM> *m_gfmBlocks;
public:

    ParserGFM(FileReader *file);
    void parserHeaderBlock(QByteArray *bodyBlock,BlockGFMData *data);
    void parserToolInfoBlock(QByteArray *bodyBlock,BlockGFMData *data);
    void parserDataBlock(QByteArray *bodyBlock,BlockGFMData *data);
    void parserUnknownBlock(QByteArray *bodyBlock,BlockGFMData *data);
    ~ParserGFM();
};

#endif // ParserGFM_H
