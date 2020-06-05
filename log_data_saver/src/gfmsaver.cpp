#include "gfmsaver.h"
#include <QFile>
#include "ablock.h"
#include "formsblock.h"
#include <QDebug>
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
#include "datablock.h"
#include "toolinfoblock.h"
#include"acurve.h"
#include "formsblock.h"
#include "unknownblock.h"
#include "headerblock.h"
#include <QFileDialog>
#include "specItem.h"

GFMSaver::GFMSaver(){

}

GFMSaver::~GFMSaver(){

}
bool GFMSaver::save(){
    if(!m_blocks){
        qDebug() << "Нечего сохранять,добавьте данные";
    }
    QDateTime date;
    QString stringDate = date.currentDateTime().toString("dd_MM_yyyy_hh_mm");
    QString fileName = QFileDialog::getSaveFileName(nullptr,"Сохранить файл как",stringDate,"GFM(*.gfm)");
    QFile *fileGFM = new QFile(fileName);
    m_codec = QTextCodec::codecForMib(1015);
    fileGFM->open(QIODevice::WriteOnly);// | QIODevice::Append);
    fileGFM->write(m_codec->fromUnicode("GFM"));
    fileGFM->write(m_codec->fromUnicode("\r\n").mid(2));

    foreach(auto block,*m_blocks){
        if(block->name() == IBlock::DATA_BLOCK)
            fileGFM->write(getForSaveDataBlock(block.data()));
        else if(block->name() == IBlock::FORMS_BLOCK)
           fileGFM->write(getForSaveFormsBlock(block.data()));
        else if(block->name() == IBlock::HEADER_BLOCK)
            fileGFM->write(getForSaveHeaderBlock(block.data()));
        else if(block->name() == IBlock::TOOLINFO_BLOCK)
            fileGFM->write(getForSaveToolInfoBlock(block.data()));
    }
    fileGFM->close();
    delete fileGFM;
    fileGFM = nullptr;
    return true;
}


bool GFMSaver::isReady(){
    return false;
}



QByteArray  GFMSaver::getForSaveDataBlock(IBlock *block){
    QByteArray blockForWrite;
    DataBlock *dataBlock = dynamic_cast<DataBlock *>(block);
    if(!dataBlock){
        qDebug() << "Не удалось перевести IBlock в DataBlock";
        return QByteArray();
    }
    QString f_name = "[DATA_BLOCK]";
    int f_nameSize = f_name.size() * 2;
    blockForWrite.append(reinterpret_cast<char*>(&f_nameSize),2);       //Размер названия блока
    blockForWrite.append(m_codec->fromUnicode(f_name).mid(2));          //Название блока

    QByteArray f_header = getHeader(dataBlock);

    int f_headerSize = f_header.size() + 4;
    QByteArray f_data;

    QList<ICurve*> *m_curves = dataBlock->curves();

    foreach(auto value,*m_curves){
        f_data.append(value->data());
    }
    int f_dataBlockSize = f_headerSize  + f_data.size() + 12;
    if(f_dataBlockSize % 2){
        ++f_dataBlockSize;
        f_data.append('0');
    }
    blockForWrite.append(reinterpret_cast<char*>(&f_dataBlockSize),4);   //Размер Дата Блока
    blockForWrite.append(reinterpret_cast<char*>(&f_headerSize),4);      //Размер заголовка
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));

    blockForWrite.append(f_header);                                      //Заголовок

    int f_numberofVector = dataBlock->numberOfVectors();
    blockForWrite.append(reinterpret_cast<char*>(&f_numberofVector),4); //Количество векторов

    blockForWrite.append(f_data);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));

    return blockForWrite;
}

QByteArray GFMSaver::getHeader(DataBlock * dataBlock){
    QByteArray headerParameters;
    QString param = "<PARAMETERS LOG=\"" + dataBlock->nameRecord() + "\">\r\n";
    QList<ShortCut> *f_shortCut = dataBlock->shortCuts();
    foreach(auto value,*f_shortCut){
        QString f_str = "<SHORTCUT REF=\"{%1}\" NAME=\"%2\"/>\r\n";
        f_str = f_str.arg(value.ref()).arg(value.name());
        param.append(f_str);
    }

    QList<ICurve*> *f_curves = dataBlock->curves();
    foreach(auto curve,*f_curves){
        ACurve *curveAbstract =  dynamic_cast<ACurve *>(curve);
        if(!curveAbstract){
            qDebug() << "Не удаётся перевести ICurve in ACurve (saver getHeader)";
        }

        QByteArray f_blockForWrite;
        QString f_line;

        QString f_recordPoint = "";
        if(qIsNaN(curveAbstract->recordPoint())){
            f_line = "[%1][%2]  {%3}:%4 : %5%6 %7\r\n";
        }
        else{
            f_line = "[%1][%2]  {%3}:%4 : %5 : %6 %7\r\n";
            f_recordPoint = QString::number(curveAbstract->recordPoint()) + "(M)";
        }
        f_line = f_line.arg(curveAbstract->offset()).arg(curveAbstract->sizeOffsetInBytes()).arg(curveAbstract->shortCut().ref())
                .arg(curveAbstract->mnemonic()).arg(curveAbstract->dataType()).arg(f_recordPoint)
                .arg(QString(curveAbstract->desc()->forSave()));

        f_blockForWrite = f_line.toLocal8Bit();
        param.append(f_blockForWrite);
    }
    param.append("</PARAMETERS>\r\n");
    headerParameters.append(m_codec->fromUnicode(param).mid(2));
    return headerParameters;
}

QByteArray  GFMSaver::getForSave(IBlock *block){
    return QByteArray();
}

QByteArray  GFMSaver::getForSaveHeaderBlock(IBlock *block){
    QByteArray blockForWrite;

    HearedBlock *headerBlock = dynamic_cast<HearedBlock*>(block);
    if(!headerBlock){
        qDebug() << "Не удалось перевести IBlock в HearedBlock";
        return QByteArray();
    }
    QString f_name = "[HEADER]";
    int f_nameSize = f_name.size() * 2;
    blockForWrite.append(reinterpret_cast<char*>(&f_nameSize),2);       //Размер названия блока
    blockForWrite.append(m_codec->fromUnicode(f_name).mid(2));

    QByteArray f_data;
    QList<QSharedPointer<HeaderInfo> > *f_headerInfo = headerBlock->infoHeader();
    foreach(auto value,*f_headerInfo){
        f_data.append(m_codec->fromUnicode(value->name()).mid(2));
        f_data.append(m_codec->fromUnicode(value->body()).mid(2));
    }

    int f_dataBlockSize = f_data.size() + 8;
    if(f_dataBlockSize % 2){
        ++f_dataBlockSize;
        f_data.append('0');
    }
    blockForWrite.append(reinterpret_cast<char*>(&f_dataBlockSize),4);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    blockForWrite.append(f_data);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    return blockForWrite;
}

QByteArray  GFMSaver::getForSaveFormsBlock(IBlock *block){
    QByteArray blockForWrite;
    FormsBlock *formsBlock = dynamic_cast<FormsBlock *>(block);
    if(!formsBlock){
        qDebug() << "Не удалось перевести IBlock в FormsBlock";
        return QByteArray();
    }

    QString f_name = "[FORMS]";
    int f_nameSize = f_name.size() * 2;
    blockForWrite.append(reinterpret_cast<char*>(&f_nameSize),2);       //Размер названия блока
    blockForWrite.append(m_codec->fromUnicode(f_name).mid(2));
    QByteArray f_data = formBlokSave(formsBlock);
    int f_dataBlockSize = f_data.size() + 8;
    if(f_dataBlockSize % 2){
        ++f_dataBlockSize;
        f_data.append('0');
    }
    blockForWrite.append(reinterpret_cast<char*>(&f_dataBlockSize),4);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    blockForWrite.append(f_data);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    return blockForWrite;
}

QByteArray  GFMSaver::getForSaveToolInfoBlock(IBlock *block){
    QByteArray blockForWrite;
    ToolInfoBlock *f_toolInfoBlock = dynamic_cast<ToolInfoBlock *>(block);
    if(!f_toolInfoBlock){
        qDebug() << "Не удалось перевести IBlock в ToolInfoBlock";
        return QByteArray();
    }

    QString f_name = "[TOOL_INFO]";
    int f_nameSize = f_name.size() * 2;
    blockForWrite.append(reinterpret_cast<char*>(&f_nameSize),2);       //Размер названия блока
    blockForWrite.append(m_codec->fromUnicode(f_name).mid(2));
    QByteArray f_data = f_toolInfoBlock->toolInfo();
    int f_dataBlockSize = f_data.size() + 8;
    if(f_dataBlockSize % 2){
        ++f_dataBlockSize;
        f_data.append('0');
    }
    blockForWrite.append(reinterpret_cast<char*>(&f_dataBlockSize),4);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    blockForWrite.append(f_data);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    return blockForWrite;
}

bool GFMSaver::gzipCompress(QByteArray input, QByteArray &output, int level){
    output.clear();
    if(input.length()){
        int flush = 0;
        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;
        int ret = deflateInit2(&strm, qMax(-1, qMin(9, level)), Z_DEFLATED, 31, 8, Z_DEFAULT_STRATEGY);
        if (ret != Z_OK)
            return(false);
        output.clear();
        char *input_data = input.data();
        int input_data_left = input.length();
        do {
            int chunk_size = qMin(32768, input_data_left);
            strm.next_in = (unsigned char*)input_data;
            strm.avail_in = chunk_size;
            input_data += chunk_size;
            input_data_left -= chunk_size;
            flush = (input_data_left <= 0 ? Z_FINISH : Z_NO_FLUSH);
            do {
                char out[32768];
                strm.next_out = (unsigned char*)out;
                strm.avail_out = 32768;
                ret = deflate(&strm, flush);
                if(ret == Z_STREAM_ERROR){
                    deflateEnd(&strm);
                    return(false);
                }
                int have = (32768 - strm.avail_out);
                if(have > 0)
                    output.append((char*)out, have);
            } while (strm.avail_out == 0);
        } while (flush != Z_FINISH);
        (void)deflateEnd(&strm);
        return(ret == Z_STREAM_END);
    }
    else
        return(true);
}

QByteArray GFMSaver::formBlokSave(FormsBlock * formsBlock){
           QByteArray xml;
           QXmlStreamWriter xmlWriter(&xml);

           xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
           xmlWriter.writeStartDocument();     // Запускаем запись в документ

           xmlWriter.writeStartElement("forms");   // Запиываем первый элемент с его именем
           xmlWriter.writeAttribute("active_name", formsBlock->activeName());//teg forms
           for(int i = 0; i < formsBlock->boards()->size(); i++){
               ABoard* board = formsBlock->boards()->value(i);
               xmlWriter.writeStartElement("board");
               xmlWriter.writeAttribute("name", board->name());
               QList<ATrack*>*tracks = board->tracks();
               foreach(auto track,*tracks)
               {
                   QString str;
                   xmlWriter.writeStartElement("track");
                   xmlWriter.writeAttribute("name", track->name());
                   xmlWriter.writeAttribute("show_grid", QString::number(track->isGreed()));
                   xmlWriter.writeAttribute("type", "LINEAR");

                   xmlWriter.writeStartElement("begin");
                   xmlWriter.writeAttribute("value", str.setNum(track->begin()));
                   xmlWriter.writeAttribute("unit", "MM");
                   xmlWriter.writeEndElement();//close begin

                   xmlWriter.writeStartElement("width");
                   xmlWriter.writeAttribute("value", str.setNum(track->width()));
                   xmlWriter.writeAttribute("unit", "MM");
                   xmlWriter.writeEndElement();//close width

                   xmlWriter.writeStartElement("logarithm");
                   xmlWriter.writeAttribute("logarithm_base", str.setNum(track->logarithmBase()));
                   xmlWriter.writeAttribute("decades_count", str.setNum(track->decadeCount()));
                   xmlWriter.writeAttribute("decade_start", str.setNum(track->decadeStart()));
                   xmlWriter.writeAttribute("decade_end", str.setNum(track->decadeEnd()));
                   xmlWriter.writeEndElement(); //close logarithm
                   QMap<QString,AItem*> *items = board->items();
                   foreach(auto item,*items){
                       if(track->number() == item->numberOfTrack())
                       {
                           if(item->type() == TypeItem::LINE){
                                LineItem * lineItem = dynamic_cast<LineItem *>(item);
                                xmlWriter.writeStartElement("line");
                                xmlWriter.writeAttribute("name", lineItem->name());
                                xmlWriter.writeAttribute("visible", lineItem->visible());

                                 xmlWriter.writeStartElement("paint_mode");
                                 xmlWriter.writeAttribute("mode", lineItem->paintMode());
                                xmlWriter.writeEndElement();//close paint mode

                                xmlWriter.writeStartElement("style");
                                xmlWriter.writeAttribute("color", lineItem->color());
                                xmlWriter.writeAttribute("dashes", str.setNum(lineItem->isDashes()));

                                xmlWriter.writeStartElement("width");
                                xmlWriter.writeAttribute("value", str.setNum(lineItem->widthLine()));
                                xmlWriter.writeAttribute("unit", "PIX");
                                xmlWriter.writeEndElement();//close width
                                xmlWriter.writeEndElement();//close style

                                xmlWriter.writeStartElement("begin");
                                xmlWriter.writeAttribute("set_begin_value", str.setNum(lineItem->isBeginValue()));
                                xmlWriter.writeAttribute("begin_value", str.setNum(lineItem->beginValue()));

                                xmlWriter.writeStartElement("zero_offset");
                                xmlWriter.writeAttribute("value", str.setNum(lineItem->zeroOffset()));
                                xmlWriter.writeAttribute("unit", "MM");
                                xmlWriter.writeEndElement();//close zero_offset
                                xmlWriter.writeEndElement();//close begin

                                xmlWriter.writeStartElement("end");
                                xmlWriter.writeAttribute("set_end_value", str.setNum(lineItem->isEndValue()));
                                xmlWriter.writeAttribute("end_value", str.setNum(lineItem->endValue()));
                                xmlWriter.writeStartElement("value_scale");
                                xmlWriter.writeAttribute("value", str.setNum(lineItem->scale()));
                                xmlWriter.writeAttribute("unit", "MM");
                                xmlWriter.writeEndElement();//close value_scale
                                xmlWriter.writeEndElement();//close end

                                xmlWriter.writeStartElement("multi_scale");
                                xmlWriter.writeAttribute("is_multi_scale", str.setNum(lineItem->isMultiScale()));
                                xmlWriter.writeAttribute("gleam_count", str.setNum(lineItem->glemCount()));
                                xmlWriter.writeAttribute("gleam_scale", str.setNum(lineItem->glemScale()));
                                xmlWriter.writeEndElement();//close multi_scale

                                xmlWriter.writeEndElement();//close line
                          }
                          if(item->type() == TypeItem::ACU){
                                AcuItem * acuItem = dynamic_cast<AcuItem *>(item);
                                xmlWriter.writeStartElement("acu");
                                xmlWriter.writeAttribute("name", acuItem->name());
                                xmlWriter.writeAttribute("visible", acuItem->visible());

                                xmlWriter.writeStartElement("style");
                                 xmlWriter.writeAttribute("show_mode", str.setNum(acuItem->showMode()));

                                xmlWriter.writeStartElement("transparent");
                                xmlWriter.writeAttribute("color", acuItem->transparentColor());
                                xmlWriter.writeEndElement();//close transparent

                                xmlWriter.writeStartElement("multi_color");
                                xmlWriter.writeAttribute("level_count",str.setNum(acuItem->levelCount()));
                                QList<MulticolorItem> *f_multicolorList = acuItem->multiColor();
                                foreach(auto multicolor,*f_multicolorList){
                                    xmlWriter.writeStartElement("level");
                                    xmlWriter.writeAttribute("bound",str.setNum(multicolor.bound));
                                    xmlWriter.writeAttribute("color",multicolor.value);
                                    xmlWriter.writeEndElement();//close level
                               }

                               xmlWriter.writeEndElement();//close multi_color

                                xmlWriter.writeStartElement("bruch_color");
                                xmlWriter.writeAttribute("color",acuItem->bruchColor());
                                xmlWriter.writeEndElement();//close bruch_color
                                xmlWriter.writeEndElement();//close style

                                xmlWriter.writeStartElement("begin");
                                xmlWriter.writeAttribute("set_begin_value", str.setNum(acuItem->isBeginValue()));
                                xmlWriter.writeAttribute("begin_value", str.setNum(acuItem->beginValue()));

                                xmlWriter.writeStartElement("zero_offset");
                                xmlWriter.writeAttribute("value", str.setNum(acuItem->zeroOffset()));
                                xmlWriter.writeAttribute("unit", "MM");
                                xmlWriter.writeEndElement();//close zero_offset
                                xmlWriter.writeEndElement();//close begin

                                xmlWriter.writeStartElement("end");
                                xmlWriter.writeAttribute("set_end_value", str.setNum(acuItem->isEndValue()));
                                xmlWriter.writeAttribute("end_value", str.setNum(acuItem->endValue()));

                                xmlWriter.writeStartElement("step_scale");
                                xmlWriter.writeAttribute("value", str.setNum(acuItem->scale()));
                                xmlWriter.writeAttribute("unit", "MM");
                                xmlWriter.writeEndElement();//close value_scale

                                xmlWriter.writeEndElement();//close end

                                xmlWriter.writeEndElement();//close acu
                        }
                          if(item->type() == TypeItem::SPEC){
                                SpecItem * specItem = dynamic_cast<SpecItem *>(item);
                                xmlWriter.writeStartElement("spec");
                                xmlWriter.writeAttribute("name", specItem->name());
                                xmlWriter.writeAttribute("visible", specItem->visible());

                                xmlWriter.writeStartElement("style");
                                 xmlWriter.writeAttribute("show_mode", str.setNum(specItem->showMode()));

                                xmlWriter.writeStartElement("transparent");
                                xmlWriter.writeAttribute("color", specItem->transparentColor());
                                xmlWriter.writeEndElement();//close transparent

                                xmlWriter.writeStartElement("multi_color");
                                xmlWriter.writeAttribute("level_count",str.setNum(specItem->levelCount()));
                                QList<MulticolorItem> *f_multicolorList = specItem->multiColor();
                                foreach(auto multicolor,*f_multicolorList){
                                    xmlWriter.writeStartElement("level");
                                    xmlWriter.writeAttribute("bound",str.setNum(multicolor.bound));
                                    xmlWriter.writeAttribute("color",multicolor.value);
                                    xmlWriter.writeEndElement();//close level
                               }

                               xmlWriter.writeEndElement();//close multi_color

                                xmlWriter.writeStartElement("bruch_color");
                                xmlWriter.writeAttribute("color",specItem->bruchColor());
                                xmlWriter.writeEndElement();//close bruch_color
                                xmlWriter.writeEndElement();//close style

                                xmlWriter.writeStartElement("begin");
                                xmlWriter.writeAttribute("set_begin_value", str.setNum(specItem->isBeginValue()));
                                xmlWriter.writeAttribute("begin_value", str.setNum(specItem->beginValue()));

                                xmlWriter.writeStartElement("zero_offset");
                                xmlWriter.writeAttribute("value", str.setNum(specItem->zeroOffset()));
                                xmlWriter.writeAttribute("unit", "MM");
                                xmlWriter.writeEndElement();//close zero_offset
                                xmlWriter.writeEndElement();//close begin

                                xmlWriter.writeStartElement("end");
                                xmlWriter.writeAttribute("set_end_value", str.setNum(specItem->isEndValue()));
                                xmlWriter.writeAttribute("end_value", str.setNum(specItem->endValue()));

                                xmlWriter.writeStartElement("value_scale");
                                xmlWriter.writeAttribute("value", str.setNum(specItem->scale()));
                                xmlWriter.writeAttribute("unit", "MM");
                                xmlWriter.writeEndElement();//close value_scale

                                xmlWriter.writeEndElement();//close end

                                xmlWriter.writeEndElement();//close spec
                        }
                        if(item->type() == TypeItem::MARK){
                           markItem * MarkItem = dynamic_cast<markItem *>(item);
                           xmlWriter.writeStartElement("mark");
                           xmlWriter.writeAttribute("name", MarkItem->name());
                           xmlWriter.writeAttribute("visible", MarkItem->visible());

                           xmlWriter.writeStartElement("style");
                           xmlWriter.writeAttribute("color", MarkItem->color());
                           xmlWriter.writeAttribute("dashes", str.setNum(MarkItem->isDashes()));

                           xmlWriter.writeStartElement("width");
                           xmlWriter.writeAttribute("value", str.setNum(MarkItem->widthLine()));
                           xmlWriter.writeAttribute("unit", "PIX");
                           xmlWriter.writeEndElement();//close width
                           xmlWriter.writeEndElement();//close style

                           xmlWriter.writeStartElement("value_scale");
                           xmlWriter.writeAttribute("value", str.setNum(MarkItem->valueScale()));
                           xmlWriter.writeAttribute("unit", "MM");
                           xmlWriter.writeEndElement();//close value_scale

                           xmlWriter.writeEndElement();//close mark
                       }
                    }
                  }
                   xmlWriter.writeEndElement();//close track
               }
               xmlWriter.writeEndElement();//close board
           }
           xmlWriter.writeEndElement();//close forms
           xmlWriter.writeEndDocument();
           QByteArray forms;
           gzipCompress(xml,forms,2);
           return forms;

}
