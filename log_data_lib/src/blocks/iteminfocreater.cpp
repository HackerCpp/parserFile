#include "iteminfocreater.h"
#include "lineItem.h"
#include "acuItem.h"
#include "markItem.h"
#include "specItem.h"

ItemInfoCreater::ItemInfoCreater(){

}

ItemInfoCreater::~ItemInfoCreater(){

}

void calculateRainbow(SpecItem *spectrItem,ICurve *curve){
    if(!spectrItem)
        return;
    QString valueRange = curve->desc()->param("val_range");
    qreal f_minimumValue = /*curve->minimum();*/ valueRange.left(valueRange.indexOf("..")).toDouble();
    qreal f_maximumValue = /*curve->maximum();*/valueRange.mid(valueRange.indexOf("..") + 2).toDouble();

    if(f_minimumValue > f_maximumValue){
        qreal min = f_maximumValue;
        f_maximumValue = f_minimumValue;
        f_minimumValue = min;
    }

    spectrItem->setMulticolor(MulticolorItem{f_minimumValue,"#ffffffff"});
    spectrItem->setMulticolor(MulticolorItem{f_minimumValue,"#ff8e00ff"});
    spectrItem->setMulticolor(MulticolorItem{f_minimumValue,"#ff0000ff"});
    spectrItem->setMulticolor(MulticolorItem{f_minimumValue,"#ff197fff"});
    spectrItem->setMulticolor(MulticolorItem{f_minimumValue,"#ff007f00"});
    spectrItem->setMulticolor(MulticolorItem{f_minimumValue,"#ffffff00"});
    spectrItem->setMulticolor(MulticolorItem{f_minimumValue,"#ffff9900"});
    spectrItem->setMulticolor(MulticolorItem{f_maximumValue,"#ffff0000"});

    QList<MulticolorItem> *f_listMulticolor = spectrItem->multiColor();

    if(f_listMulticolor->first().bound > f_listMulticolor->last().bound){
        qreal f_bound = f_listMulticolor->first().bound;
        f_listMulticolor->first().bound = f_listMulticolor->last().bound;
        f_listMulticolor->last().bound = f_bound;
    }
    qreal f_step = (f_maximumValue - f_minimumValue) / qreal(f_listMulticolor->size() - 1);

    for(int i = 1; i < f_listMulticolor->size() - 1; ++i){
        f_listMulticolor->operator[](i).bound = (f_minimumValue + (f_step * qreal(i)));
    }
}

void calculateColorAcuStandart(AcuItem *acuItem,ICurve *curve){
    if(!acuItem)
        return;
    QString valueRange = curve->desc()->param("val_range");
    qreal f_minimumValue = /*curve->minimum();*/ valueRange.left(valueRange.indexOf("..")).toDouble();
    qreal f_maximumValue = /*curve->maximum();*/valueRange.mid(valueRange.indexOf("..") + 2).toDouble();

    if(f_minimumValue > f_maximumValue){
        qreal min = f_maximumValue;
        f_maximumValue = f_minimumValue;
        f_minimumValue = min;
    }

    acuItem->setMulticolor(MulticolorItem{f_minimumValue,"#ffffffff"});
    acuItem->setMulticolor(MulticolorItem{f_minimumValue,"#ff8e00ff"});
    acuItem->setMulticolor(MulticolorItem{f_minimumValue,"#ff0000ff"});
    acuItem->setMulticolor(MulticolorItem{f_minimumValue,"#ff197fff"});
    acuItem->setMulticolor(MulticolorItem{f_minimumValue,"#ff007f00"});
    acuItem->setMulticolor(MulticolorItem{f_minimumValue,"#ffffff00"});
    acuItem->setMulticolor(MulticolorItem{f_minimumValue,"#ffff9900"});
    acuItem->setMulticolor(MulticolorItem{f_maximumValue,"#ffff0000"});

    QList<MulticolorItem> *f_listMulticolor = acuItem->multiColor();

    if(f_listMulticolor->first().bound > f_listMulticolor->last().bound){
        qreal f_bound = f_listMulticolor->first().bound;
        f_listMulticolor->first().bound = f_listMulticolor->last().bound;
        f_listMulticolor->last().bound = f_bound;
    }
    qreal f_step = (f_maximumValue - f_minimumValue) / qreal(f_listMulticolor->size() - 1);

    for(int i = 1; i < f_listMulticolor->size() - 1; ++i){
        f_listMulticolor->operator[](i).bound = (f_minimumValue + (f_step * qreal(i)));
    }
}

QString colors[] = {"#ff0000ff","#ff007f00","#ffff0000","#ff8e00ff"};

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
    else if(f_drawType == "ACOUSTIC"){
        AcuItem *f_acuItem = new AcuItem();
        f_item = f_acuItem;
        f_item->setBegin(true,0,0);
        bool ok = true;
        QString f_dataStep = curve->desc()->param("data_step");
        qreal f_dataStepD =  f_dataStep.left(f_dataStep.indexOf("(")).replace(",",".").toDouble(&ok);

        f_item->setEnd(true,curve->sizeOffset() * f_dataStepD,0.001);
        QString valueRange = curve->desc()->param("val_range");
        if(valueRange.isEmpty()){
            QString f_valueRange = QString::number(curve->minimum()) + ".." + QString::number(curve->maximum());
            curve->desc()->setParam("val_range",f_valueRange);
        }
        calculateColorAcuStandart(f_acuItem,curve);
        f_acuItem->setBrushColor(colors[qrand() % 4]);
        f_acuItem->setTransparentColor(colors[qrand() % 4]);
    }
    else if(f_drawType == "SPECTRUM"){
        SpecItem *f_spectrItem = new SpecItem();
        f_item = f_spectrItem;
        f_item->setBegin(true,0,0);
        bool ok = true;
        QString f_dataStep = curve->desc()->param("data_step");
        qreal f_dataStepD =  f_dataStep.left(f_dataStep.indexOf("(")).toDouble(&ok);
                                                           //kHz
        f_item->setEnd(true,(curve->sizeOffset() * f_dataStepD)/1000,1);

        calculateRainbow(f_spectrItem,curve);
    }
    if(f_item){
        f_item->setName(curve->shortCut().nameWithoutNumber() + ':' + curve->mnemonic(),nullptr);
        f_item->setVisible((AItem::BOARD_GRAPH_VIEW),false);
    }
    return f_item;
}
