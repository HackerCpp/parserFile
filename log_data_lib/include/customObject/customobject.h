#ifndef CUSTOMOBJECT_H
#define CUSTOMOBJECT_H
#include "primitive.h"


class CustomObject
{
    QString m_name;
    QList<Primitive *> *m_listPrimitives;
public:
    CustomObject();
    ~CustomObject();

    void setName(QString name){m_name = name;}
    void addPrimitive(Primitive *primitive);

    QString name(){return m_name;}
    QList<Primitive *> *primitives(){return m_listPrimitives;}
};

#endif // CUSTOMOBJECT_H
