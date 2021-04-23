#ifndef DATABLOCK_H
#define DATABLOCK_H

#include "ablock.h"
#include "icurve.h"
#include "shortcut.h"

class DataBlock : public ABlock{
    Q_OBJECT

    QList<ICurve*> *m_curves;
    ICurve *m_mainTime;
    ICurve *m_mainDepth;

    uint m_numberOfVectors; //Количество данных в каждой кривой
    QString m_nameRecord;
    QString m_moduleMnemonics;
    QString m_plugins;
    QList<ShortCut> *m_shortCuts;

public:
    DataBlock();
    DataBlock(DataBlock &block);
    ~DataBlock()override;

    void setNumberOfVectors(uint numberOfVectors);
    void setPlugins(QString plugins);
    void setModuleMnemonic(QString moduleMnemonics);
    void setNameRecord(QString nameRecord);
    void addShortCut(ShortCut shortCut);
    void setCurves(QList<ICurve*>curves);
    void setcurve(ICurve* curve);
    void setMainTime(ICurve *time){m_mainTime = time;}
    void setMainDepth(ICurve *depth){m_mainDepth = depth;}

    bool removeCurveOne(ICurve *curve);

    uint numberOfVectors(){return m_numberOfVectors;}
    QList<ICurve*> *curves();
    QList<ShortCut> *shortCuts();
    QString nameRecord();
    QString moduleMnemonic(){return m_moduleMnemonics;}
    QString plugins(){return m_plugins;}
    ICurve *time(){return m_mainTime;}
    ICurve *depth(){return m_mainDepth;}

signals:
    void dataUpdate();

};

#endif // DATABLOCK_H
