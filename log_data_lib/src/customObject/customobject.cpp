#include "customobject.h"


CustomObject::CustomObject()
{
    m_listPrimitives = new QList<Primitive *>();
}

CustomObject::~CustomObject(){
    if(m_listPrimitives){
        foreach(auto primitive,*m_listPrimitives){
            if(primitive){delete primitive;primitive = nullptr;}
        }
        delete m_listPrimitives; m_listPrimitives = nullptr;
    }
}

void CustomObject::addPrimitive(Primitive *primitive){
    if(m_listPrimitives)
        m_listPrimitives->push_back(primitive);

}
