#include "inc/models/modelgfm.h"
#include "inc/graphic/curveline.h"
#include "inc/graphic/spectr.h"
#include "inc/tabs/graphicsview.h"
//#include "inc/graphic/grid.h"
#include "inc/graphic/wave.h"
#include <QDebug>
#include <QTextCodec>
#include <QGraphicsSceneWheelEvent>

ModelGFM::ModelGFM(DataBlockCurve *mainValue,QList<DataBlockCurve> *curves){
    scaleFactor.m_mainValueMax = INT_MIN;
    scaleFactor.m_mainValueMin = INT_MAX;
    m_curves = curves;
    scaleFactor.m_width = 500;
    scaleFactor.m_indexBegin = scaleFactor.m_indexEnd = 0;
    scaleFactor.m_scaleY = 1;
    m_mainValue = mainValue->data;
    foreach (auto val, *m_mainValue) {
        scaleFactor.m_mainValueMax = scaleFactor.m_mainValueMax < val?val:scaleFactor.m_mainValueMax;
        scaleFactor.m_mainValueMin = scaleFactor.m_mainValueMin > val?val:scaleFactor.m_mainValueMin;
    }
    /*foreach(auto val, *m_curves){
        if(val.size/val.sizeofType == 1){
            CurveLine * curvel = new CurveLine(&scaleFactor,m_mainValue,val.data);
            this->addItem(curvel);
        }

    }*/
    foreach(auto val, *m_curves){
        if(val.size/val.sizeofType > 1){
            Wave *spectr = new Wave(&scaleFactor,m_mainValue,val.data,val.size/val.sizeofType);
            this->addItem(spectr);
        }

    }
    foreach(auto val, *m_curves){
        if(val.size/val.sizeofType > 1){
            Spectr *spectr = new Spectr(&scaleFactor,m_mainValue,val.data,val.size/val.sizeofType);
            this->addItem(spectr);
        }

    }

    //Grid *grid =  new Grid(&scaleFactor);
    //this->addItem(grid);
}

void ModelGFM::keyPressEvent(QKeyEvent *event){
  switch (event->key()){
    case Qt::Key_Q:
      scaleFactor.m_scaleY>100?scaleFactor.m_scaleY-=100:scaleFactor.m_scaleY;
      break;
    case Qt::Key_W:
      scaleFactor.m_scaleY+=100;
      break;
  }
  setSceneRect(-50,0,scaleFactor.m_width,items().last()->boundingRect().height());
  update();
}
void ModelGFM::scrollChange(qreal leftX,qreal topY,qreal rightX,qreal downY){
   scaleFactor.m_indexBegin = topY;
   scaleFactor.m_indexEnd = downY;
   scaleFactor.m_width = rightX -  leftX - 100;
   setSceneRect(-50,0,scaleFactor.m_width,items().last()->boundingRect().height());
   update();
}
void ModelGFM::connectView(){
    if(this->views().isEmpty()){
        qDebug() << "модель не имеет ни одного представления";
        return;
    }
    OGLGraphicsView *view = dynamic_cast<OGLGraphicsView *>(this->views().first());
    if(view){
        connect(view,&OGLGraphicsView::scrollChange,this,&ModelGFM::scrollChange);
    }
    else
        qDebug() << "Представление не соответствует OGLGraphicsView ";
}
