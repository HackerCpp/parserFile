#ifndef DATABLOCK_H
#define DATABLOCK_H

#include "ablock.h"
#include "icurve.h"
#include "shortcut.h"

class DataBlock : public ABlock{
    QList<ICurve*> *m_curves;
    ICurve *m_mainTime;
    ICurve *m_mainDepth;

    uint m_numberOfVectors;
    QString m_nameRecord;
    QString m_moduleMnemonics;
    QString m_plugins;
    QList<ShortCut> *m_shortCuts;

public:
    DataBlock();
    ~DataBlock();

    void setNumberOfVectors(uint numberOfVectors);
    void setPlugins(QString plugins);
    void setModuleMnemonic(QString moduleMnemonics);
    void setNameRecord(QString nameRecord);
    void addShortCut(ShortCut shortCut);
    void setCurves(QList<ICurve*>curves);
    void setcurve(ICurve* curve);

    uint numberOfVectors();
    QList<ICurve*> *curves();
    QList<ShortCut> *shortCuts();


};

#endif // DATABLOCK_H
