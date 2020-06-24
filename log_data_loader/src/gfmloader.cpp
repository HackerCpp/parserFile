#include "gfmloader.h"
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
#include "headerblock.h"
#include "addCurve.h"
#include "specItem.h"

bool GFMLoader::gzipDecompress(QByteArray input, QByteArray &output){
    output.clear();
    if(input.length() > 0){
        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;
        int ret = inflateInit2(&strm, 31);

        if (ret != Z_OK)
            return(false);
        char *input_data = input.data();
        int input_data_left = input.length();
        do {
            int chunk_size = qMin(32768, input_data_left);
            if(chunk_size <= 0)
                break;
            strm.next_in = (unsigned char*)input_data;
            strm.avail_in = chunk_size;
            input_data += chunk_size;
            input_data_left -= chunk_size;
            do {
                char out[32768];
                strm.next_out = (unsigned char*)out;
                strm.avail_out = 32768;
                ret = inflate(&strm, Z_NO_FLUSH);

                switch (ret) {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                case Z_STREAM_ERROR:
                    inflateEnd(&strm);
                    return(false);
                }
                int have = (32768 - strm.avail_out);
                if(have > 0)
                    output.append((char*)out, have);
            } while (strm.avail_out == 0);
        } while (ret != Z_STREAM_END);
        inflateEnd(&strm);
        return (ret == Z_STREAM_END);
    }
    else
        return true;
}



struct BlockByte{
    int sizeNameBlock;
    QString nameBlock;
    uint sizeBodyBlock;
    QByteArray bodyBlock;
};

void findBlocksByteFFFE(QByteArray byteArrayFile,QList<BlockByte> *blocksList,int position){
    int indexBeginBlock = byteArrayFile.indexOf("[",position);
    int indexEndBlock = byteArrayFile.indexOf("]",position) + 1;
    if(indexBeginBlock == -1 || indexEndBlock == -1)
        return;
    int sizeNameBlock = *byteArrayFile.mid(indexBeginBlock - 2,2).data();
    if(sizeNameBlock != (indexEndBlock - indexBeginBlock + 1))
        findBlocksByteFFFE(byteArrayFile,blocksList,indexEndBlock+1);
    else{
        BlockByte block;
        uint sizeDataBlock = *reinterpret_cast<uint*>(byteArrayFile.mid(indexEndBlock + 1, 4).data());
        block.sizeNameBlock = sizeNameBlock;
        block.nameBlock = byteArrayFile.mid(indexBeginBlock,sizeNameBlock).toHex();
        block.nameBlock = QByteArray::fromHex(block.nameBlock.remove("00").toLocal8Bit());
        block.sizeBodyBlock = sizeDataBlock;
        if(sizeDataBlock > INT_MAX/2){
            block.bodyBlock = byteArrayFile.mid(indexEndBlock+9);
            blocksList->push_back(block);
            return;
        }
        else{
            block.bodyBlock = byteArrayFile.mid(indexEndBlock + 9,static_cast<int>(sizeDataBlock - 8));
        }
        blocksList->push_back(block);
        findBlocksByteFFFE(byteArrayFile,blocksList,indexEndBlock + 9 + static_cast<int>(sizeDataBlock - 8));
    }
}
/******************************************************************************************************/
/****************** Public *************************************/

GFMLoader::GFMLoader(QString path){
    m_path = path;
    m_codec = QTextCodec::codecForMib(1015);

}

GFMLoader::~GFMLoader(){

}

bool GFMLoader::download(){
    start();
    return true;
}

void GFMLoader::run(){
    m_isReady = false;
    QTime time = QTime::currentTime();
    qDebug() << "begin load gfm";
    QFile file(m_path);
    file.open(QIODevice::ReadOnly);
    QByteArray byteArrayFile = file.readAll();
    file.close();
    QString bom = byteArrayFile.mid(0,2).toHex();
    QList<BlockByte> *blocksList = new QList<BlockByte>;
    if(bom == "fffe"){
        m_codec = QTextCodec::codecForMib(1015);
        findBlocksByteFFFE(byteArrayFile,blocksList,0);
    }
    if(blocksList->isEmpty())
        return;

    foreach(BlockByte value,*blocksList){
        QString name = value.nameBlock;
        IBlock::TypeBlock f_type = IBlock::NO_BLOCK;
        if(name == "[HEADER]"){
            f_type = IBlock::HEADER_BLOCK;
        }
        else if(name == "[TOOL_INFO]"){
            f_type = IBlock::TOOLINFO_BLOCK;
        }
        else if(name == "[FORMS]"){
            f_type = IBlock::FORMS_BLOCK;
        }
        else if(name == "[DATA_BLOCK]"){
            f_type = IBlock::DATA_BLOCK;
        }
        if(f_type == IBlock::NO_BLOCK)
            continue;
        IBlock *f_block = IBlock::blockCreater(f_type);
        if(!f_block)
            continue;
        parser(value.bodyBlock,f_block);
        m_blocks->push_back(f_block);
        value.bodyBlock.clear();
    }
    delete blocksList;
    byteArrayFile.clear();
    qDebug() << "end load gfm : " << time.msecsTo( QTime::currentTime() ) << "mS";
    m_isReady = true;
    emit ready();
}

void GFMLoader::parser(const QByteArray &bodyBlock,IBlock *block){

    if(block->name() == IBlock::DATA_BLOCK)
        parserDataBlock(bodyBlock,block);
    else if(block->name() == IBlock::FORMS_BLOCK)
        parserFormsBlock(bodyBlock,block);
    else if(block->name() == IBlock::HEADER_BLOCK)
        parserHeaderBlock(bodyBlock,block);
    else if(block->name() == IBlock::TOOLINFO_BLOCK)
        parserToolInfoBlock(bodyBlock,block);
    else
        parserUnknownBlock(bodyBlock,block);
}

void GFMLoader::parserHeaderBlock(const QByteArray &bodyBlock,IBlock *block){
    HearedBlock * hearedBlock = dynamic_cast<HearedBlock*>(block);
    if(!hearedBlock){
        qDebug() <<  "не удалось преобразовать IBlock в HearedBlock. Парсер дата блока";
        return;
    }
    QString endName = "]";
    QString beginName = "[";
    QString endLine = "\r\n";
    QString body = " ";
    QString nameHeader;
    QString bodyHeader;
    body += m_codec->toUnicode(bodyBlock);

    while(body.size() != 0){
        int IndexEndName = body.indexOf(endName);
        int IndexBeginName = body.indexOf(beginName);
        if(IndexBeginName == -1){
          return;
        }
        QSharedPointer<HeaderInfo> f_info(new HeaderInfo());
        nameHeader = body.mid(IndexBeginName,IndexEndName-IndexBeginName+1);
        f_info->setName(nameHeader);
        body = body.mid(IndexEndName+1, body.size() - IndexEndName);
        IndexBeginName = body.indexOf(beginName);
        int IndexLineOff = body.indexOf(endLine);
        bodyHeader = body.mid(0,IndexBeginName);
        f_info->setBody(bodyHeader);
        body = body.mid(IndexLineOff+2, body.size() - IndexLineOff);
        hearedBlock->setHeaderInfo(f_info);
    }
}

void GFMLoader::parserDataBlock(const QByteArray &bodyBlock,IBlock *block){
    DataBlock * dataBlock = dynamic_cast<DataBlock *>(block);
    if(!dataBlock){
        qDebug() <<  "не удалось преобразовать IBlock в DataBlock. Парсер дата блока";
        return;
    }
    QByteArray endHeader = "</PARAMETERS>",beginHeader = "<PARAMETERS",
            beginPlugin = "<PLUGINS>", endPlugins = "</PLUGINS>";

    int beginHeaderIndex = bodyBlock.indexOf(m_codec->fromUnicode(beginHeader).mid(4));

    int endHeaderIndex = bodyBlock.indexOf(m_codec->fromUnicode(endHeader).mid(4));

    QByteArray header = bodyBlock.mid(beginHeaderIndex - 2,endHeaderIndex - beginHeaderIndex + endHeader.size() * 2);


    int beginPluginsIndex = bodyBlock.indexOf(m_codec->fromUnicode(beginPlugin).mid(4),endHeaderIndex + endHeader.size() * 2);
    int endPluginsIndex = bodyBlock.indexOf(m_codec->fromUnicode(endPlugins).mid(4), endHeaderIndex + endHeader.size() * 2);
    int indexBeginData = 0;
    uint numberOfVectors = 0;
    if(beginPluginsIndex == -1){
        indexBeginData = endHeaderIndex + endHeader.size() * 2 + 6;
        numberOfVectors = *reinterpret_cast<uint*>(bodyBlock.mid(endHeaderIndex+endHeader.size() * 2 + 2,4).data());
    }
    else{
        indexBeginData = endPluginsIndex + endPlugins.size()*2+6;
        QString plugins = m_codec->toUnicode(bodyBlock.mid(beginPluginsIndex - 2,endPluginsIndex - beginPluginsIndex + endPlugins.size() * 2));
        dataBlock->setPlugins(plugins);
        numberOfVectors = *reinterpret_cast<uint*>(bodyBlock.mid(endPluginsIndex+endPlugins.size() * 2 + 2,4).data());
    }
    dataBlock->setNumberOfVectors(numberOfVectors);
    QByteArray nameStartMark = "NAME=\"",moduleMnemEndMarc = "\"/>";
    int indexBeginName = header.indexOf(m_codec->fromUnicode(nameStartMark).mid(4)) + nameStartMark.size() * 2 + 2;
    int indexEndName = header.indexOf(".",indexBeginName);
    QString nameRecord = m_codec->toUnicode(header.mid(indexBeginName - 4,indexEndName - indexBeginName + 4));
    dataBlock->setNameRecord(nameRecord);
    int indexEndmoduleMnem = header.indexOf(m_codec->fromUnicode(moduleMnemEndMarc).mid(4),indexEndName);
    QString moduleMnemonics = m_codec->toUnicode(header.mid(indexEndName+2,indexEndmoduleMnem - indexEndName - 4));
    dataBlock->setModuleMnemonic(moduleMnemonics);
    findShortCuts(&header,dataBlock);
    findCurves(&header,dataBlock);
    copyData(bodyBlock,indexBeginData,dataBlock);
    QList<ICurve*> *f_curves = dataBlock->curves();
    ICurve *f_mainTime = nullptr;
    ICurve *f_mainDepth = nullptr;
    foreach(auto curve,*f_curves){
        if(curve->desc()->param("draw_type") == "TIME"){
            f_mainTime = curve;
            dataBlock->setMainTime(curve);
        }
        else if(curve->desc()->param("draw_type") == "DEPTH"){
            f_mainDepth = curve;
            dataBlock->setMainDepth(curve);
        }
    }
    foreach(auto curve,*f_curves){
        if(f_mainTime){
            curve->setTime(f_mainTime);
        }
        if(f_mainDepth){
            curve->setDepth(f_mainDepth);
        }
    }

}

void GFMLoader::parserToolInfoBlock(const QByteArray &bodyBlock,IBlock *block){
    ToolInfoBlock * f_toolInfoBlock = dynamic_cast<ToolInfoBlock *>(block);
    if(!f_toolInfoBlock){
        qDebug() <<  "не удалось преобразовать IBlock в ToolInfoBlock. Парсер дата блока";
        return;
    }
    f_toolInfoBlock->setToolInfo(bodyBlock);
}

qreal convertUnitOfGFM(QString value, QString unit){     //изменение единиц измерения из заданных в мм + пересчет значения в qreal
    value = value.replace(",",".");
    qreal f_result = 0;
    if(unit == "CM")
       f_result =  value.toDouble() * 10;
    else if(unit == "M")
        f_result = value.toDouble() * 1000;
    else if(unit == "PIX" || unit == "MM")
        f_result = value.toDouble();
    else
        qDebug() << "Неизвестная величина" << unit;
    return f_result;
}

QString convertUnitInGFM(qreal value){ // изменение единиц измерения для записи в gfm
    value = value/10;
    QString help;
    help = help.setNum(value);
    return help.replace(".",",");
}

void findSettingsForItem(QXmlStreamReader *xmlReader,QString name){
    while(!xmlReader->atEnd() && !xmlReader->hasError()){
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        QXmlStreamAttributes attributes = xmlReader->attributes();
        if(xmlReader->name() == name && token == QXmlStreamReader::EndElement){
            return;
        }
    }
}

void findItemLine(QXmlStreamReader *xmlReader,ABoard *board,LineItem *lineItem){
    bool m_isBegin;
    bool m_isEnd;
    double m_begin;
    double m_end;
    while(!xmlReader->atEnd() && !xmlReader->hasError()){
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        QXmlStreamAttributes attributes = xmlReader->attributes();

        if(xmlReader->name() == "paint_mode" && token == QXmlStreamReader::StartElement){
            lineItem->setPaintMode(attributes.value("mode").toString());
        }
        else if(xmlReader->name() == "style" && token == QXmlStreamReader::StartElement){
                QString f_color = attributes.value("color").toString();
                lineItem->setColor(f_color,attributes.value("dashes").toInt());
        }
        else if(xmlReader->name() == "width" && token == QXmlStreamReader::StartElement){
            lineItem->setWidth(convertUnitOfGFM(attributes.value("value").toString(),attributes.value("unit").toString()));
        }
        else if(xmlReader->name() == "begin" && token == QXmlStreamReader::StartElement){
            m_isBegin = attributes.value("set_begin_value").toInt();
            m_begin =attributes.value("begin_value").toDouble();
        }
        else if(xmlReader->name() == "zero_offset" && token == QXmlStreamReader::StartElement){
            qreal m_zeroOffeset = convertUnitOfGFM(attributes.value("value").toString(),attributes.value("unit").toString());//attributes.value("unit").toString()
            lineItem->setBegin(m_isBegin,m_begin,m_zeroOffeset);
        }
        else if(xmlReader->name() == "end" && token == QXmlStreamReader::StartElement){
            m_isEnd = attributes.value("set_end_value").toInt();
            m_end = attributes.value("end_value").toDouble();
        }
        else if(xmlReader->name() == "value_scale" && token == QXmlStreamReader::StartElement){
            qreal m_scale = convertUnitOfGFM(attributes.value("value").toString(),attributes.value("unit").toString());
            lineItem->setEnd(m_isEnd,m_end,m_scale);
        }
        else if(xmlReader->name() == "multi_scale" && token == QXmlStreamReader::StartElement){
            lineItem->setMultiScale(attributes.value("is_multi_scale").toInt(),attributes.value("gleam_count").toDouble(),attributes.value("gleam_scale").toDouble());
        }
        else if(xmlReader->name() == "line"  && token == QXmlStreamReader::EndElement){
            AItem * item = dynamic_cast<AItem *>(lineItem);
            board->setItem(item->name(), item);
            return;
        }
    }
}

void findItemMark(QXmlStreamReader *xmlReader,ABoard *board,markItem *markItem){
    while(!xmlReader->atEnd() && !xmlReader->hasError()){
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        QXmlStreamAttributes attributes = xmlReader->attributes();
        if(xmlReader->name() == "style" && token == QXmlStreamReader::StartElement){
            markItem->setColor(attributes.value("color").toString(),attributes.value("dashes").toInt());
        }
        else if(xmlReader->name() == "width" && token == QXmlStreamReader::StartElement){
            markItem->setWidth(attributes.value("value").toDouble());
        }
        else if(xmlReader->name() == "value_scale" && token == QXmlStreamReader::StartElement){
            markItem->setValueScale(convertUnitOfGFM(attributes.value("value").toString(),attributes.value("unit").toString()));
        }
        else if( xmlReader->name() == "mark"  && token == QXmlStreamReader::EndElement){
            AItem * item = dynamic_cast<AItem *>(markItem);
            board->setItem(item->name(),item);
            return;
        }
    }
}

void findItemAcu(QXmlStreamReader *xmlReader,ABoard *board,AcuItem *acuItem){
    bool m_isBegin;
    bool m_isEnd;
    double m_begin;
    double m_end;
    QString color;
    while(!xmlReader->atEnd() && !xmlReader->hasError()){
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        QXmlStreamAttributes attributes = xmlReader->attributes();
        if(xmlReader->name() == "style" && token == QXmlStreamReader::StartElement){
            acuItem->setShowMode(attributes.value("show_mode").toInt());
        }
        else if(xmlReader->name() == "transparent" && token == QXmlStreamReader::StartElement){
           color =  attributes.value("color").toString();
        }
        else if(xmlReader->name() == "multi_color" && token == QXmlStreamReader::StartElement){
            acuItem->setLevelCount(attributes.value("level_count").toInt());
        }
        else if(xmlReader->name() == "level" && token == QXmlStreamReader::StartElement){
            MulticolorItem f_multicolor;
            f_multicolor.bound = attributes.value("bound").toDouble();
            f_multicolor.value = attributes.value("color").toString();
            acuItem->setMulticolor(f_multicolor);
        }
        else if(xmlReader->name() == "brush_color" && token == QXmlStreamReader::StartElement){
            acuItem->setColor(attributes.value("color").toString(),color);
        }
        else if(xmlReader->name() == "begin" && token == QXmlStreamReader::StartElement){
            m_isBegin=attributes.value("set_begin_value").toInt();
            m_begin = attributes.value("begin_value").toDouble();
        }
        else if(xmlReader->name() == "zero_offset" && token == QXmlStreamReader::StartElement){
            qreal m_zeroOffeset = convertUnitOfGFM(attributes.value("value").toString(),attributes.value("unit").toString());
            acuItem->setBegin(m_isBegin,m_begin,m_zeroOffeset);

        }
        else if(xmlReader->name() == "end" && token == QXmlStreamReader::StartElement){
            m_isEnd = attributes.value("set_end_value").toInt();
            m_end = attributes.value("end_value").toDouble();

        }
        else if(xmlReader->name() == "step_scale" && token == QXmlStreamReader::StartElement){
            qreal m_scale = convertUnitOfGFM(attributes.value("value").toString(),attributes.value("unit").toString());

            acuItem->setEnd(m_isEnd,m_end,m_scale);

        }
        else if(xmlReader->name() == "acu" && token == QXmlStreamReader::EndElement){
            AItem * item = dynamic_cast<AItem *>(acuItem);
            board->setItem(item->name(),item);
            return;
        }
    }
}

void findItemSpec(QXmlStreamReader *xmlReader,ABoard *board,SpecItem *specItem){
    QString colorSpec;
    bool m_isBegin;
    bool m_isEnd;
    double m_begin;
    double m_end;

    while(!xmlReader->atEnd() && !xmlReader->hasError()){
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        QXmlStreamAttributes attributes = xmlReader->attributes();

        if(xmlReader->name() == "style" && token == QXmlStreamReader::StartElement){
            specItem->setShowMode(attributes.value("show_mode").toInt());
        }
        else if(xmlReader->name() == "transparent" && token == QXmlStreamReader::StartElement){
           colorSpec =  attributes.value("color").toString();
        }
        else if(xmlReader->name() == "multi_color" && token == QXmlStreamReader::StartElement){
            specItem->setLevelCount(attributes.value("level_count").toInt());
        }
        else if(xmlReader->name() == "level" && token == QXmlStreamReader::StartElement){
            MulticolorItem f_multicolor;
            f_multicolor.bound = attributes.value("bound").toDouble();
            f_multicolor.value = attributes.value("color").toString();
            specItem->setMulticolor(f_multicolor);
        }
        else if(xmlReader->name() == "brush_color" && token == QXmlStreamReader::StartElement){
            specItem->setColor(attributes.value("color").toString(),colorSpec);
        }
        else if(xmlReader->name() == "begin" && token == QXmlStreamReader::StartElement){
           m_isBegin=attributes.value("set_begin_value").toInt();
            m_begin = attributes.value("begin_value").toDouble();
        }
        else if(xmlReader->name() == "zero_offset" && token == QXmlStreamReader::StartElement){
            qreal m_zeroOffeset = convertUnitOfGFM(attributes.value("value").toString(),attributes.value("unit").toString());
            specItem->setBegin(m_isBegin,m_begin,m_zeroOffeset);

        }
        else if(xmlReader->name() == "end" && token == QXmlStreamReader::StartElement){
            m_isEnd = attributes.value("set_end_value").toInt();
            m_end = attributes.value("end_value").toDouble();

        }
        else if(xmlReader->name() == "value_scale" && token == QXmlStreamReader::StartElement){
            qreal m_scale = convertUnitOfGFM(attributes.value("value").toString(),attributes.value("unit").toString());

            specItem->setEnd(m_isEnd,m_end,m_scale);

        }
        else if(xmlReader->name() == "spec" && token == QXmlStreamReader::EndElement){
            AItem * item = dynamic_cast<AItem *>(specItem);
            board->setItem(item->name(),item);
            return;
        }
    }
}

void findTrack(QXmlStreamReader *xmlReader,ABoard *board,ATrack *track){
    while(!xmlReader->atEnd() && !xmlReader->hasError()){
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        QXmlStreamAttributes attributes = xmlReader->attributes();
        if(xmlReader->name() == "begin" && token == QXmlStreamReader::StartElement){
            track->setBegin(convertUnitOfGFM(attributes.value("value").toString(),attributes.value("unit").toString()));
        }
        else if(xmlReader->name() == "width" && token == QXmlStreamReader::StartElement){
            track->setWidth(convertUnitOfGFM(attributes.value("value").toString(),attributes.value("unit").toString()));
        }
        else if(xmlReader->name() == "logarithm" && token == QXmlStreamReader::StartElement){
            qreal log_base = attributes.value("logarithm_base").toDouble();
            qreal dec_count = attributes.value("decades_count").toDouble();
            qreal dec_start = attributes.value("decade_start").toDouble();
            qreal dec_end = attributes.value("decade_end").toDouble();
            track->setLogarithm(log_base,dec_count,dec_start,dec_end);
        }
        else if((xmlReader->name() == "line") && token == QXmlStreamReader::StartElement){
            LineItem *f_item = new LineItem();
            f_item->setTypeItem(LINE);
            f_item->setName(attributes.value("name").toString(),attributes.value("visible").toString());
            f_item->setNumberOfTrack(track->number());
            findItemLine(xmlReader,board,f_item);
        }
        else if((xmlReader->name() == "mark") && token == QXmlStreamReader::StartElement){
            markItem *f_item = new markItem();
            f_item->setTypeItem(MARK);
            f_item->setName(attributes.value("name").toString(),attributes.value("visible").toString());
            f_item->setNumberOfTrack(track->number());
            findItemMark(xmlReader,board,f_item);
        }
        else if((xmlReader->name() == "acu") && token == QXmlStreamReader::StartElement){
            AcuItem *f_item = new AcuItem();
            f_item->setTypeItem(ACU);
            f_item->setName(attributes.value("name").toString(),attributes.value("visible").toString());
            f_item->setNumberOfTrack(track->number());
            findItemAcu(xmlReader,board,f_item);
        }
        else if((xmlReader->name() == "spec") && token == QXmlStreamReader::StartElement){
            SpecItem *f_item = new SpecItem();
            f_item->setTypeItem(SPEC);
            f_item->setName(attributes.value("name").toString(),attributes.value("visible").toString());
            f_item->setNumberOfTrack(track->number());
            findItemSpec(xmlReader,board,f_item);
        }
        else if(xmlReader->name() == "track" && token == QXmlStreamReader::EndElement){
            board->setTrack(track);
            return;
        }

    }
}

void findBoard(QXmlStreamReader *xmlReader,ABoard *board,FormsBlock *formsBlock){
    while(!xmlReader->atEnd() && !xmlReader->hasError()){
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        QXmlStreamAttributes attributes = xmlReader->attributes();
        if(xmlReader->name() == "board" && token == QXmlStreamReader::EndElement){
             formsBlock->addBoard(board);
             return;
        }
        else if(xmlReader->name() == "track" && token == QXmlStreamReader::StartElement){
            ATrack *f_track = new Track();
            f_track->setName(attributes.value("name").toString());
            QString a = f_track->name().remove("Track");
            f_track->setNumber(a.toInt());

            f_track->setIsGreed(attributes.value("show_grid").toInt());
            if(attributes.value("type").toString() == "LINEAR"){
                Types h = LINEAR;
                f_track->setType(h);
            }
            findTrack(xmlReader,board,f_track);
        }
    }
}

void GFMLoader::parserFormsBlock(const QByteArray &bodyBlock,IBlock *block){
    QTime time = QTime::currentTime();

    FormsBlock * formsBlock = dynamic_cast<FormsBlock *>(block);
    if(!formsBlock){
        qDebug() <<  "не удалось преобразовать IBlock в FormsBlock. Парсер дата блока";
    }
    QByteArray xml;
    gzipDecompress(bodyBlock,xml);
    QXmlStreamReader xmlReader(xml);
    ABoard *f_board = nullptr;
    while(!xmlReader.atEnd() && !xmlReader.hasError()){
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        QXmlStreamAttributes attributes = xmlReader.attributes();
        if(xmlReader.name() == "forms" && token == QXmlStreamReader::StartElement){
            formsBlock->setActiveName(attributes.value("active_name").toString());
        }
        else if(xmlReader.name() == "board" && token == QXmlStreamReader::StartElement){
            f_board = new Board();
            f_board->setName(attributes.value("name").toString());
            findBoard(&xmlReader,f_board,formsBlock);

        }
    }

    QFile file("forms.txt");
    file.open(QIODevice::WriteOnly);
    QByteArray output;
    gzipDecompress(bodyBlock,output);
    file.write(output);
    file.close();

    qDebug() << "end load forms : " << time.msecsTo( QTime::currentTime() ) << "mS";
}

void GFMLoader::parserUnknownBlock(const QByteArray &bodyBlock,IBlock *block){

}

void GFMLoader::findShortCuts(QByteArray *header,DataBlock *dataBlock){
   QString body = " ";
   body += m_codec->toUnicode(*header);

   QByteArray f_header = m_codec->toUnicode(*header).toLocal8Bit();
   QByteArray f_refBegin = "<SHORTCUT REF=\"{";
   QByteArray f_refEnd = "}";
   QByteArray f_nameBegin = "NAME=\"";
   QByteArray f_nameEnd = "\"/>";
   for(int pos = 0; pos < f_header.size();){
       ShortCut f_shortCut;
       int indexBeginRef = f_header.indexOf(f_refBegin,pos) + f_refBegin.size();
       if(indexBeginRef - f_refBegin.size() == -1)
           return;
       int indexEndRef   = f_header.indexOf(f_refEnd,indexBeginRef);
       if(indexEndRef == -1)
           return;
       f_shortCut.setRef(f_header.mid(indexBeginRef,indexEndRef - indexBeginRef));
       int indexBeginName = f_header.indexOf(f_nameBegin,indexEndRef) + f_nameBegin.size();
       if(indexBeginName - f_nameBegin.size() == -1)
           return;
       int indexEndName = f_header.indexOf(f_nameEnd,indexBeginName);
       if(indexEndName == -1)
           return;
       f_shortCut.setName(f_header.mid(indexBeginName,indexEndName - indexBeginName));
       pos = indexEndName;
       dataBlock->addShortCut(f_shortCut);
   }

}

void GFMLoader::findCurves(QByteArray *header,DataBlock * dataBlock){
    QString BeginLine = "] ";
    QString endLine = "\r\n";
    QList<ICurve*> *curves = new QList<ICurve*>;
    QByteArray f_header = m_codec->toUnicode(*header).toLocal8Bit();
    QList<QByteArray> f_blockLines;

    for(int i = 0; i < f_header.size();){
        int indexEndLine = f_header.indexOf(endLine,i);
        if(indexEndLine == -1){
            break;
        }
        QByteArray f_line = f_header.mid(i,indexEndLine - i);
        if(f_line.indexOf("[") == 0)
            f_blockLines.push_back(f_line);
        i += f_line.size() + 2;
    }

    foreach(QByteArray value,f_blockLines){
        if(value.indexOf("UINT8") != -1)
            curves->push_back(new Curve<uint8_t>());
        else if(value.indexOf("INT8") != -1)
            curves->push_back(new Curve<int8_t>);
        else if(value.indexOf("UINT32") != -1)
            curves->push_back(new Curve<uint32_t>);
        else if(value.indexOf("INT32") != -1)
            curves->push_back(new Curve<int32_t>);
        else if(value.indexOf("UINT16") != -1)
            curves->push_back(new Curve<uint16_t>);
        else if(value.indexOf("INT16") != -1)
            curves->push_back(new Curve<int16_t>);
        else if(value.indexOf("FLOAT32") != -1)
            curves->push_back(new Curve<float_t>);
        else if(value.indexOf("DOUBLE64") != -1)
            curves->push_back(new Curve<double>);
        else if(value.indexOf("UINT64") != -1)
            curves->push_back(new Curve<uint64_t>);
        else if(value.indexOf("INT64") != -1)
            curves->push_back(new Curve<int64_t>);
        findCurveInfo(value,dataBlock,dynamic_cast<ICurve *>(curves->last()));
    }
    dataBlock->setCurves(*curves);
}

void GFMLoader::findCurveInfo(QByteArray curveLine,DataBlock *dataBlock,ICurve *curve){
    ACurve *curveAbstract =  dynamic_cast<ACurve *>(curve);
    int indexEndOffset = curveLine.indexOf("]",1) - 1;
    uint offset = curveLine.mid(1,indexEndOffset).toUInt();
    curveAbstract->setOffset(offset);

    int indexEndsize = curveLine.indexOf("]",indexEndOffset+2) - 3;
    uint size = curveLine.mid(indexEndOffset+3,indexEndsize - indexEndOffset).toUInt();
    curveAbstract->setSizeOffset(size);

    int indexShortCutBegin = curveLine.indexOf("{",indexEndsize);
    int indexShortCutEnd = curveLine.indexOf("}",indexShortCutBegin);
    QString f_shortCut = curveLine.mid(indexShortCutBegin + 1,indexShortCutEnd - indexShortCutBegin - 1);

    QList<ShortCut> shortCuts = *dataBlock->shortCuts();
    ShortCut shortCut;
    foreach(auto value,shortCuts){
        if (f_shortCut == value.ref()){
            shortCut.setRef(value.ref());
            shortCut.setName(value.name());
        }
    }
    curveAbstract->setShortCut(shortCut);

    int indexBeginParamMnemon = curveLine.indexOf(":",indexShortCutEnd);
    int indexEndParamMnemon =   curveLine.indexOf(":",indexBeginParamMnemon + 1);
    QString mnemonics = curveLine.mid(indexBeginParamMnemon+1,indexEndParamMnemon - indexBeginParamMnemon - 2);
    curveAbstract->setMnemonic(mnemonics);

    int indexBeginType = curveLine.indexOf(":",indexEndParamMnemon);
    int indexEndType = curveLine.indexOf(" ",indexBeginType + 4);
    //QString dataType = curveLine.mid(indexBeginType + 2,indexEndType - indexBeginType - 2);
    //curveAbstract->setDataType(dataType);

    int indexEndRecordPoint = indexEndType;
    if(!shortCut.ref().isEmpty()){
        int indexBeginRecordPoint = curveLine.indexOf(":",indexEndType);
        indexEndRecordPoint = curveLine.indexOf(" ",indexBeginRecordPoint + 3);
        QString recordPoint = curveLine.mid(indexBeginRecordPoint + 2,indexEndRecordPoint - indexBeginRecordPoint - 2).replace(",",".");
        bool ok;
        qreal f_recordPointValue = recordPoint.left(recordPoint.indexOf("(")).toDouble(&ok);
        QString f_recordPointUnit = recordPoint.mid(recordPoint.indexOf("(") + 1).remove(")");
        if(ok){
            if(f_recordPointUnit == "СМ" || f_recordPointUnit == "CM")
                f_recordPointValue = f_recordPointValue / 100;
            else if(f_recordPointUnit == "M" || f_recordPointUnit == "М" ){
                ;
            }
            else{
                qDebug() << "Неизвестная величина gfmloader.cpp при переводе точки записи"  << f_recordPointUnit;
            }
            curveAbstract->setRecordPoint(f_recordPointValue);
        }
    }
    Desc *desc = new Desc(curveLine.mid(indexEndRecordPoint));
    curveAbstract->setDesc(desc);
}

void GFMLoader::copyData(QByteArray bodyBlock,int indexBeginData,DataBlock *dataBlock){
    uint numberOfVectors = dataBlock->numberOfVectors();
    QList<ICurve*> *curves = dataBlock->curves();
    if(!curves){
        qDebug() << "дата блок вернул нулевой указатель на кривые";
        return;
    }
    foreach (auto curve,*curves){
        ACurve * f_curve = dynamic_cast<ACurve *>(curve);
        if(!f_curve)
            continue;
        uint offset = f_curve->offset() * numberOfVectors;
        curve->setData(bodyBlock.data() + indexBeginData + offset,numberOfVectors);
    }
}

