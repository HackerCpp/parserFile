#include "track.h"

Track::Track(){

}

void Track::parser(QByteArray *byteArray){
    int indexBeginName = byteArray->indexOf("name=\"") + QByteArray("name=\"").size();
    int indexEndName = byteArray->indexOf("\"",indexBeginName);
    m_name = byteArray->mid(indexBeginName,indexEndName - indexBeginName);
    int indexBeginGrid = byteArray->indexOf("show_grid=\"") + QByteArray("show_grid=\"").size();
    int indexEndGrid = byteArray->indexOf("\"",indexBeginGrid);
    m_isShowGrid = byteArray->mid(indexBeginGrid,indexEndGrid - indexBeginGrid).toInt();
    int indexBeginType = byteArray->indexOf("type=\"") + QByteArray("type=\"").size();
    int indexEndType = byteArray->indexOf("\"",indexBeginType);
    m_type = byteArray->mid(indexBeginType,indexEndType - indexBeginType);
    int indexBeginLeft = byteArray->indexOf("<begin value=\"") + QByteArray("<begin value=\"").size();
    int indexEndLeft = byteArray->indexOf("\"",indexBeginLeft);
    m_leftPosition = static_cast<int>(byteArray->mid(indexBeginLeft,indexEndLeft - indexBeginLeft).replace(',','.').toDouble() * 10);
    int indexBeginWidth = byteArray->indexOf("<width value=\"") + QByteArray("<width value=\"").size();
    int indexEndWidth = byteArray->indexOf("\"",indexBeginWidth);
    m_width = static_cast<int>(byteArray->mid(indexBeginWidth,indexEndWidth - indexBeginWidth).replace(',','.').toDouble() * 10);
}

Track::~Track(){

}
