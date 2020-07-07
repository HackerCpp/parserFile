#include "spectrviewer.h"
#include "graphicitemforspectr.h"
#include <QScrollBar>


SpectrViewer::SpectrViewer(VSpectrItem *spectrItem,int width){
    m_scene = new SpectrScene;
    m_radioBtnIsActive = new QRadioButton("ACtive",this);
    m_originalSpectr = spectrItem;
    m_experimentalSpectr = new VSpectrItem(*spectrItem);
    if(m_experimentalSpectr){
        m_experimentalSpectr->updateParam(width);
        m_scene->addItem(new GraphicItemForSpectr(m_experimentalSpectr,width));
    }
    else{
        qDebug() << "Не удалось создать копию спектра в редакторе, конструктор копирования вернул nullptr";
    }
    //m_waveWidget = new OneWaveWidget;
    //m_waveWidget->show();
    setScene(m_scene);

    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &SpectrViewer::scrollChanged);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &SpectrViewer::scrollChanged);
}

SpectrViewer::~SpectrViewer(){
    if(m_scene){delete m_scene; m_scene = nullptr;}
    ICurve * f_curve = m_experimentalSpectr->curve();
    if(f_curve){delete f_curve; f_curve = nullptr;}
    if(m_experimentalSpectr){delete m_experimentalSpectr; m_experimentalSpectr = nullptr;}
    if(m_radioBtnIsActive){delete m_radioBtnIsActive; m_radioBtnIsActive = nullptr;}
}

void SpectrViewer::changeWidth(int newWidth){
    QList<QGraphicsItem*> f_items = m_scene->items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changeSize(newWidth);
            setSceneRect(f_itemForSpectr->boundingRect());
        }
    }
}

void SpectrViewer::changeVisibilityZone(QRectF newVisibilityZone){
    QList<QGraphicsItem*> f_items = m_scene->items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changeVisibilityZone(newVisibilityZone);
            setSceneRect(f_itemForSpectr->boundingRect());
        }
    }
}

void SpectrViewer::scrollChanged(){
    QPolygonF f_rect = mapToScene(QRect(x(),y(),width(),height()));
    QRectF f_rectForScene = QRectF(f_rect[0].x(),f_rect[0].y(),f_rect[2].x() - f_rect[0].x(), f_rect[2].y() - f_rect[0].y());
    changeVisibilityZone(f_rectForScene);
}
void SpectrViewer::resizeEvent(QResizeEvent *event){
    scrollChanged();
}

void SpectrViewer::changePositionOneWave(QPoint position){
    //if(!m_waveWidget)
        //return;
    //bool f_flag;
    //m_waveWidget->update(m_experimentalSpectr->oneWave(position.y(),&f_flag));
    emit sig_changePositionOneWave(position);
}
