#include "verticalboard.h"
#include "QScrollBar"
#include "objectoftheboard.h"
#include "iteminfocreater.h"
#include "browsergraphicitems.h"



VerticalBoard::VerticalBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves)
    :AGraphicBoard(boardInfo,curves)
{
    init();
    if(!m_boardInfo){
        qDebug() << "Передан нулевой указатель bordInfo";
        return;
    }
    QList<ATrack*> *tracksInfo = m_boardInfo->tracks();
    if(!tracksInfo){
        qDebug() << "Bord:" << m_boardInfo->name() << "вернул нулевой указатель на треки";
        return;
    }
    VerticalTrack *f_prevTrack = nullptr;
    foreach(auto trackInfo,*tracksInfo){
       VerticalTrack *f_track  = new VerticalTrack(trackInfo,curves,this);
       connect(this,&VerticalBoard::changingTheVisibilityZone,f_track,&ObjectOfTheBoard::changingTheVisibilityZone);
       m_canvas->addItem(f_track);
       if(f_prevTrack){
           connect(f_prevTrack,&VerticalTrack::changedPositionBorder,f_track,&VerticalTrack::changeBegin);
       }
       f_prevTrack = f_track;
    }
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &VerticalBoard::scrollChanged);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &VerticalBoard::scrollChanged);
    updateItems();
    distributionOfItemsBetweenTracks();
    resize();
}

VerticalBoard::VerticalBoard(QMap<QString,ICurve*> *curves):AGraphicBoard(nullptr,curves){
    init();
}

VerticalBoard::VerticalBoard():AGraphicBoard(nullptr,nullptr){
    init();
}

void VerticalBoard::updateItems(){
    if(!m_curves || !m_boardInfo)
        return;
    //Создаём кривые, если нет itemInfo для них создаём и itemInfo
        QMap<QString,AItem*> *itemsInfo = m_boardInfo->items();
        foreach(auto curveKey,m_curves->keys()){
            AItem *f_itemInfo = itemsInfo->value(curveKey);
            if(!f_itemInfo){
                f_itemInfo = ItemInfoCreater::CreateItemInfo(m_curves->value(curveKey));
                if(f_itemInfo)
                    itemsInfo->insert(curveKey,f_itemInfo);
            }
            if(f_itemInfo){
                if(m_items->find(curveKey) == m_items->end()){
                    m_items->insert(curveKey,ItimsCreater::createItem(f_itemInfo,m_curves->value(curveKey),this,ItimsCreater::VERTICAL));
                }
            }
        }
}

void VerticalBoard::distributionOfItemsBetweenTracks(){
    QList<QGraphicsItem *> f_tracks = items();
    //убираеm из треков все кривые
    foreach(auto track, f_tracks){
        VerticalTrack *f_track = dynamic_cast<VerticalTrack *>(track);
        if(f_track){
            f_track->clearItems();
        }
    }
    //Распределяем кривые в треки
    foreach(auto item,*m_items){
        foreach(auto track, f_tracks){
            VerticalTrack *f_track = dynamic_cast<VerticalTrack *>(track);
            if(f_track){
                if(f_track->trackInfo()->number() == item->itemInfo()->numberOfTrack()){
                    f_track->addIteam(item);
                    break;
                }
            }
        }

    }
}

VerticalBoard::~VerticalBoard(){

}


void VerticalBoard::newTrack(){

}

void VerticalBoard::init(){
     m_canvas = new QGraphicsScene();
     setScene(m_canvas);
}

void VerticalBoard::resizeEvent(QResizeEvent *event){
    resize();
    scrollChanged();
}

void VerticalBoard::insertNewTrack(int curentTrackNumber,InsertPossition position){
    QList<QGraphicsItem *> m_items = this->items();
    QList<ATrack *> *f_listTracksInfo = m_boardInfo->tracks();
    ATrack *f_curentTrackInfo = nullptr;
    int newNumberTrack = 1;
    foreach(auto trackInfo, *f_listTracksInfo){
        newNumberTrack = newNumberTrack > trackInfo->number() ? newNumberTrack : trackInfo->number();
        if(trackInfo->number() == curentTrackNumber){
            f_curentTrackInfo = trackInfo;
            continue;
        }
    }
    newNumberTrack++;
    VerticalTrack *f_curentTrack = nullptr;
    foreach(auto item, m_items){
        VerticalTrack *f_track = dynamic_cast<VerticalTrack *>(item);
        if(f_track){
            if(f_track->trackInfo()->number() == curentTrackNumber){
              f_curentTrack = f_track;
              break;
            }
        }
    }
    ATrack * f_trackInfo = new ATrack();
    f_trackInfo->setName("Track " + QString::number(newNumberTrack));
    f_trackInfo->setType(Types::LINEAR);
    f_trackInfo->setWidth(25);
    f_trackInfo->setIsGreed(true);
    VerticalTrack *f_nextTrack = nullptr,*f_prevTrack = nullptr;
    ATrack *f_prevTrackInfo = nullptr;

    if(position == InsertPossition::RIGHT){
        f_prevTrack = f_curentTrack;
        f_prevTrackInfo = f_curentTrackInfo;

        foreach(auto item, m_items){
            VerticalTrack *f_track = dynamic_cast<VerticalTrack *>(item);
            if(f_track){
                int f_error = (f_track->trackInfo()->begin() - (f_prevTrackInfo->begin() + f_prevTrackInfo->width()));
                if(!f_error ){
                  f_nextTrack = f_track;
                  break;
                }
            }
        }

    }
    else if(position == InsertPossition::LEFT){
        f_nextTrack = f_curentTrack;

        foreach(auto trackInfo, *f_listTracksInfo){
            int f_error = (trackInfo->begin() + trackInfo->width()) - f_curentTrackInfo->begin();
            if(!f_error){
                f_prevTrackInfo = trackInfo;
                break;
            }
        }

        if(f_prevTrackInfo){
            foreach(auto item, m_items){
                VerticalTrack *f_track = dynamic_cast<VerticalTrack *>(item);
                if(f_track){
                    if(f_track->trackInfo()->number() == f_prevTrackInfo->number()){
                      f_prevTrack = f_track;
                      break;
                    }
                }
            }
        }
    }
    VerticalTrack *f_track  = new VerticalTrack(f_trackInfo,nullptr,this);
    connect(this,&VerticalBoard::changingTheVisibilityZone,f_track,&ObjectOfTheBoard::changingTheVisibilityZone);
    m_canvas->addItem(f_track);
    if(!f_prevTrack && f_nextTrack){
       f_listTracksInfo->push_front(f_trackInfo);
       f_trackInfo->setBegin(0);
       connect(f_track,&VerticalTrack::changedPositionBorder,f_nextTrack,&VerticalTrack::changeBegin);
    }
    else if(f_prevTrack && !f_nextTrack){
        f_listTracksInfo->push_back(f_trackInfo);
        f_trackInfo->setBegin(f_prevTrackInfo->begin() + f_prevTrackInfo->width());
        connect(f_prevTrack,&VerticalTrack::changedPositionBorder,f_track,&VerticalTrack::changeBegin);
    }
    else if(f_prevTrack && f_nextTrack){
        int f_indexPositionNextInfo = f_listTracksInfo->indexOf(f_nextTrack->trackInfo());
        f_trackInfo->setBegin(f_prevTrackInfo->begin() + f_prevTrackInfo->width());

        f_listTracksInfo->insert(f_indexPositionNextInfo,f_trackInfo);
        disconnect(f_prevTrack,&VerticalTrack::changedPositionBorder,f_nextTrack,&VerticalTrack::changeBegin);
        connect(f_prevTrack,&VerticalTrack::changedPositionBorder,f_track,&VerticalTrack::changeBegin);
        connect(f_track,&VerticalTrack::changedPositionBorder,f_nextTrack,&VerticalTrack::changeBegin);
    }
    f_track->changeBegin(f_track->trackInfo()->begin() * m_pixelPerMm);
    redraw();
}

void inline VerticalBoard::scrollChanged(){
    QPolygonF f_rect = mapToScene(QRect(x(),y(),width(),height()));
    if(f_rect.isEmpty()){
        qDebug() << "нулевой размер у борда, сигнал трэкам не может быть отправлен" << m_boardInfo->name();
        return;
    }
    QRectF f_rectForScene = QRectF(f_rect[0].x(),f_rect[0].y(),f_rect[2].x() - f_rect[0].x(), f_rect[2].y() - f_rect[0].y());
    changingTheVisibilityZone(f_rectForScene);
}

