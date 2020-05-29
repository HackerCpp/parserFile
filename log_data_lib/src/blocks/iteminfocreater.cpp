#include "iteminfocreater.h"
#include "lineItem.h"
#include "AcuItem.h"
#include "markItem.h"

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
        f_item->setName(curve->shortCut().nameWithoutNumber() + ':' + curve->mnemonic(),nullptr);
    }
    else if(f_drawType == "MARK"){
        f_item = new markItem();
    }
    /*else if(f_drawType == "ACOUSTIC"){
        f_item = new AcuItem();
    }
    */
    return f_item;
}
