#include "verticalboard.h"
#include "QScrollBar"
#include "objectoftheboard.h"
#include "iteminfocreater.h"
#include "browsergraphicitems.h"
#include "ruler.h"
#include <QDesktopWidget>
#include "acousticsEditor/acousticsEditor.h"
#include "labelitem.h"

VerticalBoard::VerticalBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves,DrawSettings *drawSettings,SetLabelsForBoard *ldLabels)
    :AGraphicBoard(boardInfo,curves,drawSettings),m_ldLabels(ldLabels)
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
    Ruler *f_ruler = new Ruler(this);
    connect(this,&VerticalBoard::changingTheVisibilityZone,f_ruler,&ObjectOfTheBoard::changingTheVisibilityZone);
    connect(this,&VerticalBoard::needToRedraw,f_ruler,&ObjectOfTheBoard::needToRedraw);

    m_canvas->addItem(f_ruler);
    foreach(auto trackInfo,*tracksInfo){
       VerticalTrack *f_track  = new VerticalTrack(trackInfo,this);
       if(!f_track)
           continue;
       connect(this,&VerticalBoard::changingTheVisibilityZone,f_track,&ObjectOfTheBoard::changingTheVisibilityZone);
       connect(this,&VerticalBoard::needToRedraw,f_track,&ObjectOfTheBoard::needToRedraw);
       m_canvas->addItem(f_track);
       if(f_prevTrack){
           connect(f_prevTrack,&VerticalTrack::changedPositionBorder,f_track,&VerticalTrack::changeBegin);
       }
       f_prevTrack = f_track;
    }
    /*LDLabel *m_ldLabel = new LDLabel(1640,1.03,1,this->boardInfo()->name(),"Text Metki");
    m_ldLabels->labels()->push_back(m_ldLabel);*/
    foreach(auto label,*m_ldLabels->labels()){
        LDLabelItem *f_lblItem = new LDLabelItem(this,label);
        m_canvas->addItem(f_lblItem);
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
    //Создаём

    if(m_legend)
        delete m_legend; m_legend = nullptr;

    m_legend = new ItemsLegendView(m_items,this);
    m_legend->move(0,0);

//Add Stadart widget*************************************
    CurvesForCalc f_curves;
    foreach(auto item,m_items->values()){
        if(item->itemInfo()->type() == TypeItem::ACU){
            if(item->curve()->mnemonic().indexOf("1") != -1)
                f_curves.m_acuOne = dynamic_cast<VAcuItem *>(item);
            else if(item->curve()->mnemonic().indexOf("2") != -1)
                f_curves.m_acuTwo = dynamic_cast<VAcuItem *>(item);
        }
        else if(item->curve()->mnemonic() == "T1(mkSec)")
            f_curves.m_t1 = dynamic_cast<VLineItem *>(item);
        else if(item->curve()->mnemonic() == "T2(mkSec)")
            f_curves.m_t2 = dynamic_cast<VLineItem *>(item);
        else if(item->curve()->mnemonic() == "DT(mkSec)")
            f_curves.m_dt = dynamic_cast<VLineItem *>(item);
        else if(item->curve()->mnemonic() == "A1(ADCU)")
            f_curves.m_a1_adcu = dynamic_cast<VLineItem *>(item);
        else if(item->curve()->mnemonic() == "A2(ADCU)")
            f_curves.m_a2_adcu = dynamic_cast<VLineItem *>(item);
        else if(item->curve()->mnemonic() == "A1(DB)")
            f_curves.m_a1_db = dynamic_cast<VLineItem *>(item);
        else if(item->curve()->mnemonic() == "A2(DB)")
            f_curves.m_a2_db = dynamic_cast<VLineItem *>(item);
        else if(item->curve()->mnemonic() == "Alpha(DB/M)")
            f_curves.m_alpha = dynamic_cast<VLineItem *>(item);
    }

    if(f_curves.m_dt && f_curves.m_t1 && f_curves.m_t2 && f_curves.m_a1_db
            && f_curves.m_a2_db && f_curves.m_alpha && f_curves.m_acuOne
            && f_curves.m_acuTwo && f_curves.m_a1_adcu  && f_curves.m_a2_adcu
            && f_curves.m_acuOne->is_visible() && f_curves.m_acuTwo->is_visible()){
        if(m_standartWidgets){
            m_standartWidgets->push_back(new AcousticsEditor(f_curves));
            //m_standartWidgets->first()->show();
        }
    }
}

LDLabelItem * VerticalBoard::addLabel(LDLabel *label){
    QList<QGraphicsItem *> f_tracks = items();
    m_ldLabels->addLabel(label);
    LDLabelItem *f_ldlItem = new LDLabelItem(this,label);
    m_canvas->addItem(f_ldlItem);
    foreach(auto track, f_tracks){
        VerticalTrack *f_track = dynamic_cast<VerticalTrack *>(track);
        if(f_track){
            if(f_track->trackInfo()->number() == f_ldlItem->ldLabel()->trackNumber()){
                f_ldlItem->addParentTrack(f_track);
                break;
            }
        }
    }
    return f_ldlItem;
}

void VerticalBoard::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        m_posLeftClick = event->pos();
        m_timerLeftClick.start(300);
    }
    else if(event->button() == Qt::LeftButton){
        m_isStandartWidget = true;
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
        if(m_isStandartWidget){
            for(auto &widget : *m_standartWidgets){
                widget->changePosition(mapToScene(event->pos()));
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
    m_isStandartWidget = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void VerticalBoard::distributionOfItemsBetweenTracks(){
    QList<QGraphicsItem *> f_tracks = items();
    QList<QGraphicsItem *> f_ldlItem = items();
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

    foreach(auto item,f_ldlItem){
        LDLabelItem *f_ldlItem = dynamic_cast<LDLabelItem *>(item);
        if(!f_ldlItem)continue;
        foreach(auto track, f_tracks){
            VerticalTrack *f_track = dynamic_cast<VerticalTrack *>(track);
            if(f_track){
                if(f_track->trackInfo()->number() == f_ldlItem->ldLabel()->trackNumber()){
                    f_ldlItem->addParentTrack(f_track);
                    break;
                }
            }
        }

    }
}

void VerticalBoard::redraw(){
    emit needToRedraw();
}

VerticalBoard::~VerticalBoard(){
    if(m_items){
        foreach(auto graphicItem,*m_items){
            if(graphicItem){graphicItem->deleteLater(); graphicItem = nullptr;}
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

void VerticalBoard::scrollChanged(){
    QPolygonF f_rect = mapToScene(QRect(0,0,width(),height()));
    if(f_rect.isEmpty()){
        qDebug() << "нулевой размер у борда, сигнал трэкам не может быть отправлен" << m_boardInfo->name();
        return;
    }
    QRectF f_rectForScene = QRectF(f_rect[0],f_rect[2]);
    emit changingTheVisibilityZone(f_rectForScene);
}

