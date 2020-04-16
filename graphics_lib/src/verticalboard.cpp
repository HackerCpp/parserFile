#include "verticalboard.h"
#include "QScrollBar"
#include "objectoftheboard.h"



VerticalBoard::VerticalBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves)
    :m_board(boardInfo)
{
    init();
    if(!m_board){
        qDebug() << "Передан нулевой указатель bordInfo";
        return;
    }
    QList<ATrack*> *tracksInfo = m_board->tracks();
    if(!tracksInfo){
        qDebug() << "Bord:" << m_board->name() << "вернул нулевой указатель на треки";
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
    resize();
}

VerticalBoard::VerticalBoard(QMap<QString,ICurve*> *curves){
    init();
}

VerticalBoard::VerticalBoard(){
    init();
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

void inline VerticalBoard::scrollChanged(){
    QPolygonF f_rect = mapToScene(QRect(x(),y(),width(),height()));
    if(f_rect.isEmpty()){
        qDebug() << "нулевой размер у борда, сигнал трэкам не может быть отправлен" << m_board->name();
        return;
    }
    QRectF f_rectForScene = QRectF(f_rect[0].x(),f_rect[0].y(),f_rect[2].x() - f_rect[0].x(), f_rect[2].y() - f_rect[0].y());
    changingTheVisibilityZone(f_rectForScene);
}

