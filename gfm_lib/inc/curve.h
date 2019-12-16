#ifndef CURVE_H
#define CURVE_H
#include <QString>
#include <QByteArray>
#include "shortcut.h"
#include "desc.h"
#include <QThread>
#include <cmath>
#include <QtGlobal>

class Curve : public QThread{
    Curve *m_mainTime;
    Curve *m_mainDepth;
protected:
    qreal m_maximum,m_minimum;
    ShortCut m_shortCut;
    uint m_size;
    uint m_sizeOfType;
    QString m_parameterMnemonics;
    QString m_dataType;
    QString m_recordPoint;
    Desc *m_desc;
    qreal m_positiveOffset;
public:
    uint m_offset;
    Curve();
    void parser(QByteArray curveLine,QList<ShortCut> *shortCuts);

    Desc *desc(){return m_desc;}
    virtual void run();
    virtual qreal data(uint index);
    virtual uint getSize();
    virtual QByteArray getDataByte();
    QByteArray getForSave();
    QString getMnemonic(){return m_parameterMnemonics;}
    ShortCut getShortCut();
    Curve *getTime(){return m_mainTime;}
    Curve *getDepth(){return m_mainDepth;}
    qreal maximum();
    qreal minimum();
    void setMainTime(Curve *mainTime);
    void setMainDepth(Curve *mainDepth);
    virtual qreal operator[](int index);
    virtual void setData(const char * dataPointer,uint numberOfVectors);
    qreal offset(){return m_positiveOffset;}
    virtual ~Curve();
};

#endif // CURVE_H
