#include "datacountingacoustics.h"

DataCountingAcoustics::DataCountingAcoustics()
{
    m_items = QVector<AGraphicItem *>(MAXIMUM);


}

bool DataCountingAcoustics::isValidItem(AGraphicItem *item){
    if(m_items[ACU_ONE] && m_items[ACU_ONE] != item){
        if(item->curve()->depth() == m_items[ACU_ONE]->curve()->depth())
            return true;
    }
    else if(m_items[ACU_TWO] && m_items[ACU_TWO] != item){
        if(item->curve()->depth() == m_items[ACU_TWO]->curve()->depth())
            return true;
    }
    return false;
}
