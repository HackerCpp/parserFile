#include "inc/datablockgfm.h"
#include <QTextCodec>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QDebug>
#include <inc/curveuint8.h>
#include <inc/curveint8.h>
#include <inc/curveuint16.h>
#include <inc/curveint16.h>
#include <inc/curveuint32.h>
#include <inc/curveint32.h>
#include <inc/curvefloat32.h>


DataBlockGFM::DataBlockGFM(){
    m_codec = QTextCodec::codecForMib(1015);
    m_shortCuts = new QList<ShortCut>;
    m_mainTime = nullptr;
    m_mainDepth = nullptr;
}

void DataBlockGFM::findShortCuts(QByteArray *header){
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
       m_shortCuts->push_back(f_shortCut);
   }

}
void DataBlockGFM::findCurves(QByteArray *header){
    QString BeginLine = "] ";
    QString endLine = "\r\n";
    m_curves = new QList<Curve*>;
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
            m_curves->push_back(new CurveUint8);
        else if(value.indexOf("INT8") != -1)
            m_curves->push_back(new CurveInt8);
        else if(value.indexOf("UINT32") != -1)
            m_curves->push_back(new CurveUint32);
        else if(value.indexOf("INT32") != -1)
           m_curves->push_back(new CurveInt32);
        else if(value.indexOf("UINT16") != -1)
            m_curves->push_back(new CurveUint16);
        else if(value.indexOf("INT16") != -1)
            m_curves->push_back(new CurveInt16);
        else if(value.indexOf("FLOAT32") != -1)
            m_curves->push_back(new CurveFloat32);
            m_curves->last()->parser(value,m_shortCuts);
    }

}
void DataBlockGFM::copyData(QByteArray *bodyBlock,int indexBeginData){
    foreach (auto curve,*m_curves){
        uint offset = curve->m_offset * m_numberOfVectors;
        curve->setData(bodyBlock->data() + indexBeginData + offset,m_numberOfVectors);
    }
}

void DataBlockGFM::parser(QByteArray *bodyBlock){
    QByteArray endHeader = "</PARAMETERS>",beginHeader = "<PARAMETERS",
            beginPlugin = "<PLUGINS>", endPlugins = "</PLUGINS>";
    int beginHeaderIndex = bodyBlock->indexOf(m_codec->fromUnicode(beginHeader).mid(4));
    int endHeaderIndex = bodyBlock->indexOf(m_codec->fromUnicode(endHeader).mid(4));
    QByteArray header = bodyBlock->mid(beginHeaderIndex - 2,endHeaderIndex - beginHeaderIndex + endHeader.size() * 2);
    int beginPluginsIndex = bodyBlock->indexOf(m_codec->fromUnicode(beginPlugin).mid(4),endHeaderIndex + endHeader.size() * 2);
    int endPluginsIndex = bodyBlock->indexOf(m_codec->fromUnicode(endPlugins).mid(4), endHeaderIndex + endHeader.size() * 2);
    int indexBeginData = 0;
    if(beginPluginsIndex == -1){
        indexBeginData = endHeaderIndex+endHeader.size() * 2 + 6;
        m_numberOfVectors = *reinterpret_cast<uint*>(bodyBlock->mid(endHeaderIndex+endHeader.size() * 2 + 2,4).data());
    }
    else{
        indexBeginData = endPluginsIndex + endPlugins.size()*2+6;
        m_plugins = m_codec->toUnicode(bodyBlock->mid(beginPluginsIndex - 2,endPluginsIndex - beginPluginsIndex + endPlugins.size() * 2));
        m_numberOfVectors = *reinterpret_cast<uint*>(bodyBlock->mid(endPluginsIndex+endPlugins.size() * 2 + 2,4).data());
    }
    QByteArray nameStartMark = "NAME=\"",moduleMnemEndMarc = "\"/>";
    int indexBeginName = header.indexOf(m_codec->fromUnicode(nameStartMark).mid(4)) + nameStartMark.size() * 2 + 2;
    int indexEndName = header.indexOf(".",indexBeginName);
    m_nameRecord = m_codec->toUnicode(header.mid(indexBeginName - 4,indexEndName - indexBeginName + 4));
    int indexEndmoduleMnem = header.indexOf(m_codec->fromUnicode(moduleMnemEndMarc).mid(4),indexEndName);
    m_moduleMnemonics = m_codec->toUnicode(header.mid(indexEndName+2,indexEndmoduleMnem - indexEndName - 4));
    findShortCuts(&header);
    findCurves(&header);
    copyData(bodyBlock,indexBeginData);

    foreach(auto curve,*m_curves){
        if(curve->desc()->getParam("draw_type") == "TIME"){
            m_mainTime = curve;
        }
        else if(curve->desc()->getParam("draw_type") == "DEPTH"){
            m_mainDepth = curve;
        }
    }
    foreach(auto curve,*m_curves){
        if(m_mainTime){
            curve->setMainTime(m_mainTime);
        }
        if(m_mainDepth){
            curve->setMainDepth(m_mainDepth);
        }
    }
}
QByteArray DataBlockGFM::getHeader(){
    QByteArray headerParameters;
    QString param = "<PARAMETERS LOG=\"" + m_nameRecord + "\">\r\n";
    foreach(auto value,*m_shortCuts){
        QString f_str = "<SHORTCUT REF=\"{%1}\" NAME=\"%2\"/>\r\n";
        f_str = f_str.arg(value.getRef()).arg(value.getName());
        param.append(f_str);
    }
    foreach(auto value,*m_curves)
        param.append(value->getForSave());
    param.append("</PARAMETERS>\r\n");
    headerParameters.append(m_codec->fromUnicode(param).mid(2));
    return headerParameters;
}
QByteArray DataBlockGFM::getForSave(){
    QByteArray blockForWrite;
    int f_nameSize = m_name.size() * 2;
    blockForWrite.append(reinterpret_cast<char*>(&f_nameSize),2);       //Размер названия блока
    blockForWrite.append(m_codec->fromUnicode(m_name).mid(2));          //Название блока
    QByteArray f_header = getHeader();
    int f_headerSize = f_header.size() + 4;
    QByteArray f_data;
    foreach(auto value,*m_curves)
        f_data.append(value->getDataByte());
    int f_dataBlockSize = f_headerSize  + f_data.size() + 12;
    blockForWrite.append(reinterpret_cast<char*>(&f_dataBlockSize),4);   //Размер Дата Блока
    blockForWrite.append(reinterpret_cast<char*>(&f_headerSize),4);      //Размер заголовка
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    blockForWrite.append(f_header);                                      //Заголовок
    blockForWrite.append(reinterpret_cast<char*>(&m_numberOfVectors),4); //Количество векторов
    blockForWrite.append(f_data);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    return blockForWrite;
}
QList<Curve*> *DataBlockGFM::getCurves(){
    return m_curves;
}
DataBlockGFM::~DataBlockGFM(){
    foreach(auto value,*m_curves)
        delete value;
    delete m_curves;
    m_curves = nullptr;
}
