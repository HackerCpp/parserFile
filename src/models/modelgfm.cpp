#include "inc/models/modelgfm.h"
#include "inc/graphic/curveline.h"
#include <QDebug>
#include <QTextCodec>

ModelGFM::ModelGFM(QList<BlockGFM> *gfmBlocks){
    int quan = 20;

    for(auto value = gfmBlocks->begin();value < gfmBlocks->end();value++){
        if(value->name == "[DATA_BLOCK]" && value->data){
            DataBlock * ptr = reinterpret_cast<DataBlock *>(value->data);
            //qDebug() << ptr->moduleMnemonics;
            for(auto val = ptr->curves->begin();val < ptr->curves->end();val++){
                CurveLine * curvel = new CurveLine(val->data);
                //if(ptr->moduleMnemonics == "GKT[30030496]" ){
                    //qDebug() << val->parameterMnemonics;
                    //if(quan > 0){
                    this->addItem(curvel);

                    //}
                    //quan--;
                //}

            }

        }
    }
    QPen pen(Qt::black);
    pen.setWidth(3);
    this->addLine(-3,0,0,this->height(),pen);
    this->addLine(500,0,500,this->height(),pen);
}
