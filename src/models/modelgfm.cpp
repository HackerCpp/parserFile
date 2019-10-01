#include "inc/models/modelgfm.h"
#include "inc/graphic/curveline.h"
#include "inc/tabs/graphicsview.h"
#include "inc/graphic/grid.h"
#include <QDebug>
#include <QTextCodec>

ModelGFM::ModelGFM(QList<BlockGFM> *gfmBlocks){

    for(auto value = gfmBlocks->begin();value < gfmBlocks->end();value++){
        if(value->name == "[DATA_BLOCK]" && value->data){
            DataBlock * ptr = reinterpret_cast<DataBlock *>(value->data);
            //qDebug() << ptr->moduleMnemonics;
            for(auto val = ptr->curves->begin();val < ptr->curves->end();val++){
                CurveLine * curvel = new CurveLine(val->data);
                connect(this,&ModelGFM::scrollChange,curvel,&BaseCurveClass::scrollChange);
                //if(ptr->moduleMnemonics == "GKT[30030496]" ){
                    //qDebug() << val->parameterMnemonics;
                    //if(quan > 0){
                        //qDebug() << val->data->size();
                    this->addItem(curvel);
                    //quan--;
                    //}

                //}

            }

        }
    }
    Grid *grid =  new Grid(this->height());
    connect(this,&ModelGFM::scrollChange,grid,&BaseCurveClass::scrollChange);
    this->addItem(grid);
    /*QPen pen(Qt::black);
    pen.setWidth(3);
    this->addLine(-3,0,0,this->height(),pen);
    this->addLine(500,0,500,this->height(),pen);*/
}

void ModelGFM::connectView(){
    if(this->views().isEmpty()){
        qDebug() << "модель не имеет ни одного представления";
        return;
    }
    OGLGraphicsView *view = dynamic_cast<OGLGraphicsView *>(this->views().first());
    if(view)
        connect(view,&OGLGraphicsView::scrollChange,this,&ModelGFM::scrollChange);
    else
        qDebug() << "Представление не соответствует OGLGraphicsView ";
}
