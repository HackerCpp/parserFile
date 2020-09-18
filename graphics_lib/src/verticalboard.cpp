#include "verticalboard.h"
#include "QScrollBar"
#include "objectoftheboard.h"
#include "iteminfocreater.h"
#include "browsergraphicitems.h"
#include "ruler.h"
#include <QDesktopWidget>




VerticalBoard::VerticalBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves,DrawSettings *drawSettings)
    :AGraphicBoard(boardInfo,curves,drawSettings)
{
    init();

    if(!m_boardInfo){
        qDebug() << "Передан нулевой указатель boardInfo";
        return;
    }
    QList<ATrack*> *tracksInfo = m_boardInfo->tracks();
    if(!tracksInfo){
        qDebug() << "Bord:" << m_boardInfo->name() << "вернул нулевой указатель на треки VerticalBoard.cpp ";
        return;
    }
    m_isShowLegend = false;
    VerticalTrack *f_prevTrack = nullptr;
    //qDebug() << m_boardInfo->name();
    Ruler *f_ruler = new Ruler(this);
    connect(this,&VerticalBoard::changingTheVisibilityZone,f_ruler,&ObjectOfTheBoard::changingTheVisibilityZone);

    m_canvas->addItem(f_ruler);
    foreach(auto trackInfo,*tracksInfo){
        //qDebug() << trackInfo->name() << trackInfo->begin() << trackInfo->width();
       VerticalTrack *f_track  = new VerticalTrack(trackInfo,this);
       if(!f_track)
           continue;
       connect(this,&VerticalBoard::changingTheVisibilityZone,f_track,&ObjectOfTheBoard::changingTheVisibilityZone);
       m_canvas->addItem(f_track);
       if(f_prevTrack){
           connect(f_prevTrack,&VerticalTrack::changedPositionBorder,f_track,&VerticalTrack::changeBegin);
       }
       f_prevTrack = f_track;
    }
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &VerticalBoard::scrollChanged);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &VerticalBoard::scrollChanged);
    //Создаём графические кривые. Если нет информации для кривой создаём.
    updateItems();
    //распределяем графические кривые между треками
    distributionOfItemsBetweenTracks();
    //Определяем размер сцены
    resize();
    //Обновляем параметры всех кривых
    updateItemsParam();

    connect(&m_timerLeftClick,&QTimer::timeout,this,&VerticalBoard::timerLeftClick);
}


VerticalBoard::VerticalBoard(QMap<QString,ICurve*> *curves,DrawSettings *drawSettings)
    :AGraphicBoard(nullptr,curves,drawSettings){
    init();
}



VerticalBoard::VerticalBoard():AGraphicBoard(nullptr,nullptr,nullptr){
    init();
}

//Создаём графические кривые. Если нет информации для кривой создаём.
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
                if(m_items->find(curveKey) == m_items->end()){ //Если графическое представление для этой кривой не создано на этом борде
                    AGraphicItem *f_graphicItem = ItimsCreater::createItem(f_itemInfo,m_curves->value(curveKey),this,ItimsCreater::VERTICAL);//Создаём
                    if(f_graphicItem){
                        m_items->insert(curveKey,f_graphicItem);//И добавляем
                    }
                }
            }
        }
        if(m_legend)
            delete m_legend; m_legend = nullptr;

        m_legend = new ItemsLegendView(m_items,this);
        m_legend->move(0,0);
}

void VerticalBoard::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        m_posLeftClick = event->pos();
        m_timerLeftClick.start(300);
    }
    QGraphicsView::mousePressEvent(event);
}

void VerticalBoard::timerLeftClick(){
    m_timerLeftClick.stop();
    if(m_legend){
        m_isShowLegend = true;
        m_beginLineLegend->setLine(0,mapToScene(m_posLeftClick).y(),m_canvas->width(),mapToScene(m_posLeftClick).y());
        m_beginLineLegend->show();
        m_currentLineLegend->setLine(0,mapToScene(m_posLeftClick).y(),m_canvas->width(),mapToScene(m_posLeftClick).y());
        m_currentLineLegend->show();
        //m_legend->move(QCursor::pos());
        m_legend->changeScenePoint(mapToScene(m_posLeftClick));
        m_legend->show();
    }
}

void VerticalBoard::mouseMoveEvent(QMouseEvent *event){
    //if(event->button() == Qt::RightButton){
        if(m_isShowLegend){
            if(m_legend){
                m_currentLineLegend->setLine(0,mapToScene(event->pos()).y(),m_canvas->width(),mapToScene(event->pos()).y());
                //m_legend->move(QCursor::pos());
                m_legend->changeScenePoint(mapToScene(event->pos()));
            }
        }
    //}
    QGraphicsView::mouseMoveEvent(event);
}
void VerticalBoard::mouseReleaseEvent(QMouseEvent *event){
    m_timerLeftClick.stop();
    if(m_isShowLegend){
        m_isShowLegend = false;
        if(m_legend){
            m_legend->hide();
            m_currentLineLegend->hide();
            m_beginLineLegend->hide();
        }
    }
    QGraphicsView::mouseReleaseEvent(event);
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
    if(m_items){
        foreach(auto graphicItem,*m_items){
            if(graphicItem){delete graphicItem; graphicItem = nullptr;}
        }
        delete m_items; m_items = nullptr;
    }
    QList<QGraphicsItem*> f_items = m_canvas->items();
    foreach(auto item,f_items){
        if(item){delete item; item = nullptr;}
    }

    if(m_canvas){delete m_canvas;m_canvas = nullptr;}
}


void VerticalBoard::newTrack(){

}

void VerticalBoard::init(){
    m_legend = nullptr;
    m_canvas = new Canvas();
    setScene(m_canvas);
    setMouseTracking(true);
    m_beginLineLegend = new QGraphicsLineItem();
    m_currentLineLegend = new QGraphicsLineItem();
    m_beginLineLegend->setPen(QPen(Qt::red,2));
    m_currentLineLegend->setPen(QPen(Qt::red,2));
    m_beginLineLegend->setZValue(200);
    m_currentLineLegend->setZValue(200);
    m_canvas->addItem(m_beginLineLegend);
    m_canvas->addItem(m_currentLineLegend);

}

void VerticalBoard::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event)
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
    VerticalTrack *f_track  = new VerticalTrack(f_trackInfo,this);
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
    f_track->changeBegin(f_track->trackInfo()->begin() * m_drawSettings->pixelPerMm());
    f_track->activate(true);
    redraw();
}

void inline VerticalBoard::scrollChanged(){
    QPolygonF f_rect = mapToScene(QRect(0,0,width(),height()));
    if(f_rect.isEmpty()){
        qDebug() << "нулевой размер у борда, сигнал трэкам не может быть отправлен" << m_boardInfo->name();
        return;
    }
    QRectF f_rectForScene = QRectF(f_rect[0],f_rect[2]);
    changingTheVisibilityZone(f_rectForScene);
}

