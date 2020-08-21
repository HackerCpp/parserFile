#include "linking.h"
#include <curve.h>
#include "desc.h"

Linking::Linking(QObject *parent)
    : QObject(parent)
{

}

ICurve *Linking::createTime(uint timeBegin_min,uint timeEnd_min,qreal step_sec){
    if(timeBegin_min > timeEnd_min){
        uint f_begin = timeBegin_min;
        timeBegin_min = timeEnd_min;
        timeEnd_min = f_begin;
    }
    int f_timeSize = static_cast<int>(qreal((timeEnd_min - timeBegin_min) * 60) / step_sec);
    ICurve *f_curve = new Curve<uint>(f_timeSize,1);
    uint f_data_mSec = timeBegin_min * 1000;//mSec
    uint f_step_mSec = static_cast<uint>(step_sec * 1000);//mSec
    for(uint i = 0; i < f_timeSize; ++i , f_data_mSec += f_step_mSec){
        f_curve->setData(f_data_mSec,i);
    }

    Desc *f_desc = new Desc();
    f_desc->setParam("draw_type","TIME");
    f_desc->setParam("resolution","1");
    f_desc->setParam("begin","{{}}");
    f_curve->setDesc(f_desc);

    f_curve->setMnemonic("TIME(MSEC)");

    return f_curve;
}

ICurve *Linking::createDepth(int depthBegin_m,int depthEnd_m,qreal step_m){
    if(depthBegin_m > depthEnd_m){
        int f_begin = depthBegin_m;
        depthBegin_m = depthEnd_m;
        depthEnd_m = f_begin;
    }
    int f_depthSize = static_cast<int>(qreal(depthEnd_m - depthBegin_m) / step_m);
    ICurve *f_curve = new Curve<int>(f_depthSize,1);
    int f_data_mm = depthBegin_m * 1000;//mm
    uint f_step_mm = static_cast<uint>(step_m * 1000);//mm
    for(uint i = 0; i < f_depthSize; ++i ,f_data_mm += f_step_mm){
        f_curve->setData(f_data_mm,i);
    }

    Desc *f_desc = new Desc();
    f_desc->setParam("draw_type","DEPTH");
    f_desc->setParam("resolution","0.1");
    f_desc->setCalib("counts","100");
    f_desc->setCalib("length","1");
    f_desc->setCalib("unit","(M)");
    f_curve->setDesc(f_desc);

    f_curve->setMnemonic("DEPTH(COUNTS)");
    return f_curve;
}

ICurve *Linking::linkTime(ICurve *mainTime,ICurve *curve){
    if( !mainTime || !curve)
        return nullptr;


    ICurve *f_curve = new Curve<uint>(0,1);

    return f_curve;
}
ICurve *Linking::linkDepth(ICurve *mainDepth,ICurve *curve){
    if(!mainDepth || !curve)
        return nullptr;

    ICurve *f_curve = new Curve<uint>(0,1);

    return f_curve;
}


