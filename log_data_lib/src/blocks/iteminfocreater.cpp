#include "iteminfocreater.h"
#include "lineItem.h"
#include "acuItem.h"
#include "markItem.h"
#include "specItem.h"

ItemInfoCreater::ItemInfoCreater(){

}

ItemInfoCreater::~ItemInfoCreater(){

}

AItem *ItemInfoCreater::CreateItemInfo(ICurve *curve){
    QString f_drawType = curve->desc()->param("draw_type");
    AItem *f_item = nullptr;
    if(f_drawType == "LINE"){
        f_item = new LineItem();
        f_item->setBegin(false,curve->minimum(),rand() % 5000);
        qreal f_maximum = curve->maximum() ? curve->maximum() : 1;
        f_item->setEnd(false,curve->maximum(),20.f/f_maximum);

    }
    else if(f_drawType == "MARK"){
        f_item = new markItem();
    }
    /*else if(f_drawType == "ACOUSTIC"){
        f_item = new AcuItem();
    }*/
    else if(f_drawType == "SPECTRUM"){
        SpecItem *f_spectrItem = new SpecItem();
        f_item = f_spectrItem;
        QString valueRange = curve->desc()->param("val_range");
        //qreal f_minimum = valueRange.left(valueRange.indexOf("..")).toDouble();
        //qreal f_maximum = valueRange.right(valueRange.indexOf("..") - 1).toDouble();
        f_item->setBegin(true,0,0);
        bool ok = true;
        QString f_dataStep = curve->desc()->param("data_step");
        qreal f_dataStepD =  f_dataStep.left(f_dataStep.indexOf("(")).toDouble(&ok);
                                                           //kHz
        f_item->setEnd(true,(curve->sizeOffset() * f_dataStepD)/1000,1);
        f_spectrItem->setMulticolor(MulticolorItem{-110,"#ffffffff"});
        f_spectrItem->setMulticolor(MulticolorItem{-108,"#ff8e00ff"});
        f_spectrItem->setMulticolor(MulticolorItem{-107,"#ff0000ff"});
        f_spectrItem->setMulticolor(MulticolorItem{-106,"#ff197fff"});
        f_spectrItem->setMulticolor(MulticolorItem{-105,"#ff007f00"});
        f_spectrItem->setMulticolor(MulticolorItem{-103,"#ffffff00"});
        f_spectrItem->setMulticolor(MulticolorItem{-102,"#ffff9900"});
        f_spectrItem->setMulticolor(MulticolorItem{-100,"#ffff0000"});
    }
    if(f_item){
        f_item->setName(curve->shortCut().nameWithoutNumber() + ':' + curve->mnemonic(),nullptr);
        f_item->setVisible((AItem::BOARD_GRAPH_VIEW),false);
    }
    return f_item;
}
