#include "graphicheader.h"
#include "headeritem.h"

GraphicHeader::GraphicHeader(IBoard *boardInfo)
    :m_items(nullptr), m_boardInfo(boardInfo)
{
    m_canvas = new QGraphicsScene(this);
    QList<ATrack*> *tracksInfo = m_boardInfo->tracks();
    if(!tracksInfo){
        qDebug() << "Bord:" << m_boardInfo->name() << " вернул нулевой указатель на треки VerticalBoard.cpp ";
        return;
    }
    foreach(auto trackInfo,*tracksInfo){
       HeaderItem *f_headerTrack  = new HeaderItem(trackInfo);
       if(!f_headerTrack)
           continue;
       m_canvas->addItem(f_headerTrack);
       /*if(f_prevTrack){
           connect(f_prevTrack,&VerticalTrack::changedPositionBorder,f_track,&VerticalTrack::changeBegin);
       }
       f_prevTrack = f_track;*/
    }

}

void GraphicHeader::addGraphicsItems(QMap<QString,AGraphicItem *> *items){
    m_items = items;
}
