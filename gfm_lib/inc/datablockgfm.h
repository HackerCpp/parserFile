#ifndef DATABLOCKGFM_H
#define DATABLOCKGFM_H
#include "abstractblockgfm.h"
#include "curve.h"
#include <QList>
#include <QThread>
#include "shortcut.h"

class DataBlockGFM : public AbstractBlockGFM{
    Curve *m_mainTime;
    Curve *m_mainDepth;
    uint m_numberOfVectors;
    QString m_nameRecord;
    QString m_moduleMnemonics;
    QString m_plugins;
    QList<Curve*> *m_curves;
    QList<ShortCut> *m_shortCuts;

    void copyData(QByteArray *bodyBlock,int indexBeginData);
    void findShortCuts(QByteArray *header);
    void findCurves(QByteArray *header);
    QByteArray getHeader();

public:
    DataBlockGFM();
    void parser(QByteArray *bodyBlock);
    virtual QByteArray getForSave();
    QList<Curve*> *getCurves();
    ~DataBlockGFM();
};

#endif // DATABLOCKGFM_H
