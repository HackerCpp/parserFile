#include "inc/curve.h"
#include <QDebug>

using namespace std;

Curve::Curve(){
    m_mainTime = nullptr;
    m_mainDepth = nullptr;
    m_desc = nullptr;
    m_positiveOffset = 0;
    m_desc = nullptr;
    m_maximum = numeric_limits<qreal>::min();
    m_minimum = numeric_limits<qreal>::max();
}
qreal Curve::maximum(){
    return m_maximum;
}
qreal Curve::minimum(){
    return m_minimum;
}

qreal Curve::data(uint index){
    return 0;
}

void Curve::parser(QByteArray curveLine,QList<ShortCut> *shortCuts){
    int indexEndOffset = curveLine.indexOf("]",1)-1;
    m_offset = curveLine.mid(1,indexEndOffset).toUInt();
    int indexEndsize = curveLine.indexOf("]",indexEndOffset+2)-3;
    m_size = curveLine.mid(indexEndOffset+3,indexEndsize - indexEndOffset).toUInt();
    int indexShortCutBegin = curveLine.indexOf("{",indexEndsize);
    int indexShortCutEnd = curveLine.indexOf("}",indexShortCutBegin);
    QString f_shortCut = curveLine.mid(indexShortCutBegin + 1,indexShortCutEnd - indexShortCutBegin - 1);
    foreach(auto value,*shortCuts){
        if (f_shortCut == value.getRef()){
            m_shortCut.setRef(value.getRef());
            m_shortCut.setName(value.getName());
        }
    }
    int indexBeginParamMnemon = curveLine.indexOf(":",indexShortCutEnd);
    int indexEndParamMnemon =   curveLine.indexOf(" ",indexBeginParamMnemon + 5);
    m_parameterMnemonics = curveLine.mid(indexBeginParamMnemon+1,indexEndParamMnemon - indexBeginParamMnemon - 1);
    int indexBeginType = curveLine.indexOf(":",indexEndParamMnemon);
    int indexEndType = curveLine.indexOf(" ",indexBeginType + 4);
    m_dataType = curveLine.mid(indexBeginType + 2,indexEndType - indexBeginType - 2);
    int indexEndRecordPoint = indexEndType;
    if(!m_shortCut.getRef().isEmpty()){
        int indexBeginRecordPoint = curveLine.indexOf(":",indexEndType);
        indexEndRecordPoint = curveLine.indexOf(" ",indexBeginRecordPoint + 3);
        m_recordPoint = curveLine.mid(indexBeginRecordPoint + 2,indexEndRecordPoint - indexBeginRecordPoint - 2);
    }
    m_desc = new Desc(curveLine.mid(indexEndRecordPoint));
}

ShortCut Curve::getShortCut(){
    return m_shortCut;
}

void Curve::run(){
    return;
}

void Curve::setData(const char * dataPointer,uint numberOfVectors){

}
void Curve::setMainTime(Curve *mainTime){
    m_mainTime = mainTime;
}
void Curve::setMainDepth(Curve *mainDepth){
    m_mainDepth = mainDepth;
}
qreal Curve::operator[](int index){
    return 0;
}

uint Curve::getSize(){
   return 0;
}

QByteArray Curve::getForSave(){
    QByteArray f_blockForWrite;
    QString f_line;
    if(m_recordPoint.isEmpty())
        f_line = "[%1][%2]  {%3}:%4 : %5%6 %7\r\n";
    else
        f_line = "[%1][%2]  {%3}:%4 : %5 : %6 %7\r\n";
    f_line = f_line.arg(m_offset).arg(m_size).arg(m_shortCut.getRef())
            .arg(m_parameterMnemonics).arg(m_dataType).arg(m_recordPoint)
            .arg(QString(m_desc->getForSave()));
    f_blockForWrite = f_line.toLocal8Bit();
    return f_blockForWrite;
}

QByteArray Curve::getDataByte(){
    QByteArray b;
    return b;
}

Curve::~Curve(){
}
