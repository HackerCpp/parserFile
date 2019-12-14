#ifndef GFM_H
#define GFM_H
#include <QString>
#include "datablockgfm.h"
#include <QList>



class GFM : public QThread{
    QString m_path;
    QString m_bom;
    QList<AbstractBlockGFM*> *m_listBlocksGFM;
    bool m_isReady;
    QTextCodec *m_codec;
    QList<Curve*> *m_curves;

    void run();
public:
    QList<AbstractBlockGFM*> *getBlocks();
    QList<DataBlockGFM*> *getDataBlocks();
    QList<Curve*> *getCurves(){return m_curves;}
    GFM(QString path);
    void saveFile(QString fileName);
    ~GFM();
};

#endif // GFM_H
