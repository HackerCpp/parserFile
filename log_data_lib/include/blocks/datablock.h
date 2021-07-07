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

    uint numberOfVectors()const{return m_numberOfVectors;}
    QList<ICurve*> *curves()const;
    QList<ShortCut> *shortCuts()const;
    QString nameRecord()const;
    QString moduleMnemonic()const{return m_moduleMnemonics;}
    QString plugins()const{return m_plugins;}
    ICurve *time()const{return m_mainTime;}
    ICurve *depth()const{return m_mainDepth;}

signals:
    void dataUpdate();

};

#endif // DATABLOCK_H
