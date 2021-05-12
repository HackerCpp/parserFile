#ifndef DATACOUNTINGACOUSTICS_H
#define DATACOUNTINGACOUSTICS_H
#include "agraphicitem.h"

class DataCountingAcoustics
{

    QVector<AGraphicItem *> m_items;
    qreal m_base;

public:
    enum AcuTypeItem{ACU_ONE,ACU_TWO,T_ONE,T_TWO,DT,A_ONEADCU,A_TWOADCU,A_ONEDB,A_TWODB,ALPHA_DBM,MAXIMUM};

    DataCountingAcoustics();
    ~DataCountingAcoustics(){}

    void setAcuItemOne(AGraphicItem *acuItem){m_items[ACU_ONE] = acuItem;}
    void setAcuItemTwo(AGraphicItem *acuItem){m_items[ACU_TWO] = acuItem;}
    void setItem(AGraphicItem *item,AcuTypeItem type){if(type == MAXIMUM)return;m_items[type] = item; }

    AGraphicItem *acuItemOne(){return m_items[ACU_ONE];}
    AGraphicItem *acuItemTwo(){return m_items[ACU_TWO];}

    AGraphicItem *tItemOne(){return m_items[T_ONE];}
    AGraphicItem *tItemTwo(){return m_items[T_TWO];}
    AGraphicItem *dtItem(){return m_items[DT];}

    AGraphicItem *amplOneADCU(){return m_items[A_ONEADCU];}
    AGraphicItem *amplTwoADCU(){return m_items[A_TWOADCU];}
    AGraphicItem *amplOneDB(){return m_items[A_ONEDB];}
    AGraphicItem *amplTwoDB(){return m_items[A_TWODB];}
    AGraphicItem *alphaDB_M(){return m_items[ALPHA_DBM];}

    AGraphicItem *item(AcuTypeItem type){if(type != MAXIMUM) return m_items[type];return nullptr;}

    QVector<AGraphicItem *> items(){return m_items;}


    bool isValidItem(AGraphicItem *item);
};

#endif // DATACOUNTINGACOUSTICS_H
