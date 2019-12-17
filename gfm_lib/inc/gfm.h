#ifndef GFM_H
#define GFM_H
#include <QString>
#include "datablockgfm.h"
#include <QList>
#include "forms.h"



class GFM : public QThread{
    QString m_path;
    QString m_bom;
    QList<AbstractBlockGFM*> *m_listBlocksGFM;
    bool m_isReady;
    QTextCodec *m_codec;
    QHash<QString,Curve*> *m_curvesHash;

    void run();
public:
    QList<AbstractBlockGFM*> *getBlocks();
    QList<DataBlockGFM*> *getDataBlocks();
    QHash<QString,Curve*> *getCurves(){return m_curvesHash;}
    Forms *getForms();
    GFM(QString path);
    void saveFile(QString fileName);
    bool isReady();
    ~GFM();
};

#endif // GFM_H
