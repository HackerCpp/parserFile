#include "agraphicboard.h"
#include <QGraphicsScene>

AGraphicBoard::AGraphicBoard(){
    m_minimumSize = 2000;
}

void AGraphicBoard::resize(){
    QList<QGraphicsItem *> m_items = this->items();
    int f_width = 0;
    qreal f_topPosition = 999999999999999999;
    qreal f_bottomPosition = -999999999999999999;
    foreach(auto item, m_items){
        int rightPosition = item->boundingRect().x() + item->boundingRect().width();
        AGraphicTrack *f_track = dynamic_cast<AGraphicTrack *>(item);
        if(f_track){
            f_topPosition = f_topPosition < f_track->topValue() ? f_topPosition : f_track->topValue();
            f_bottomPosition = f_bottomPosition > f_track->bottomValue() ? f_bottomPosition : f_track->bottomValue();
        }
        f_width = (f_width > rightPosition ? f_width : rightPosition);
    }
    m_top = f_topPosition - (20 * m_pixelPerMm);
    m_length = f_bottomPosition - m_top + (20 * m_pixelPerMm);
    if(m_length < 800)
        m_length = 800;
    setSceneRect(QRect(0,m_top,f_width,m_length));
    foreach(auto item, m_items){
        int rightPosition = item->boundingRect().x() + item->boundingRect().width();
        AGraphicTrack *f_track = dynamic_cast<AGraphicTrack *>(item);
        if(f_track){
            f_track->resize();
        }
        else{
            //qDebug() << "не удалось преобразовать QGraphicItem in AGraphicTrack;";
        }
    }
}


void AGraphicBoard::resizePicture(){
    QList<QGraphicsItem *> m_items = this->items();
    foreach(auto item, m_items){
        AGraphicTrack *f_track = dynamic_cast<AGraphicTrack *>(item);
        if(f_track){
           f_track->resizePictures();
        }
    }
}

void AGraphicBoard::activate(bool activate){
    QList<QGraphicsItem *> m_items = this->items();
    foreach(auto item, m_items){
        AGraphicTrack *f_track = dynamic_cast<AGraphicTrack *>(item);
        if(f_track){
           f_track->activate(activate);
        }
    }
}

void AGraphicBoard::setFormatTime(FormatTime format){
    setScaleForTime(1.f/qreal(m_dividersTime[format]));
    redraw();
    resize();
}

void AGraphicBoard::setFormatDepth(FormatDepth format){
    setScaleForDepth(1.f/qreal(m_dividersDepth[format]));
    redraw();
    resize();
}

void AGraphicBoard::setLengthPicture(LengthPicture format){
    setPictureHeightMM(m_lengtgPicture[format]);
    resizePicture();
    redraw();
    resize();
}

void AGraphicBoard::setFormatPicture(QImage::Format format){
    m_formatImg = format;
    resizePicture();
    redraw();
    resize();
}

void AGraphicBoard::mousePressEvent(QMouseEvent *event){
     QGraphicsView::mousePressEvent(event);
 }

 void AGraphicBoard::mouseMoveEvent(QMouseEvent *event){
     QGraphicsView::mouseMoveEvent(event);
 }

 void AGraphicBoard::mouseReleaseEvent(QMouseEvent *event){
     QGraphicsView::mouseReleaseEvent(event);
 }
