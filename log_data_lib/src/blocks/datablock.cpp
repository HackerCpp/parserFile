#include "datablock.h"



DataBlock::DataBlock(){
    m_curves = new QList<ICurve>;
}

DataBlock::~DataBlock(){
    if(m_curves){
        delete m_curves;
        m_curves = nullptr;
    }


}
